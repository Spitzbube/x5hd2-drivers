/*
 * Copyright (c) (2011 - ...) digital media project platform development dept,
 * Hisilicon. All rights reserved.
 *
 * File: msg.c
 *
 * Purpose: omx vdec msg funcs
 *
 * Author: y00226912
 *
 * Date: 16, 03, 2013
 *
 */

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/wait.h>
#include "hisi_vdec.h"
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/delay.h>

#include "common.h"
#include "msg.h"

msg_queue_s *msg_queue_init(HI_U32 max_msg_num)
{
	HI_U32 nqueues;
	msg_queue_s *queue = NULL;
	msg_data_s *data = NULL;

	OmxPrint(OMX_TRACE, "msg prepare to init.\n");
    
	queue = kzalloc(sizeof(msg_queue_s), GFP_KERNEL);
	if (NULL == queue)
       {
	       OmxPrint(OMX_FATAL, "%s call kzalloc for queue failed.\n", __func__);
		return NULL;
	}

	spin_lock_init(&queue->lock);
	INIT_LIST_HEAD(&queue->head);
	INIT_LIST_HEAD(&queue->free);
	init_waitqueue_head(&queue->wait);
	queue->stop = 0;

	/* alloc element for seg stream */
	nqueues = max_msg_num;
	data = queue->alloc = kzalloc(sizeof(msg_data_s) * nqueues, GFP_KERNEL);
	if (NULL == data) 
       {
	       OmxPrint(OMX_FATAL, "%s call kzalloc for data failed.\n", __func__);
		kfree(queue);
		return NULL;
	}

	for (; nqueues; data++, nqueues--)
       {   
		list_add(&data->list, &queue->free);
       }

	queue->msg_num = nqueues;
    
	OmxPrint(OMX_TRACE, "msg init ok.\n");
    
	return queue;
}


static HI_VOID msg_stop(msg_queue_s *queue)
{
	unsigned long flags;
	struct list_head *list, *tmp;

	OmxPrint(OMX_TRACE, "msg prepare to stop.\n");

	/* flush msg list */
	spin_lock_irqsave(&queue->lock, flags);
	queue->stop = 1;
	if (!list_empty(&queue->head)) 
       {
	       OmxPrint(OMX_WARN, "msg queue not empty, flush it!\n");
		list_for_each_safe(list, tmp, &queue->head) 
              {
			list_del(list);
			list_add_tail(list, &queue->free);
		}
	}
	spin_unlock_irqrestore(&queue->lock, flags);

	wake_up(&queue->wait);
	msleep(10);

	OmxPrint(OMX_TRACE, "msg stop ok.\n");
}


HI_VOID msg_queue_deinit(msg_queue_s *queue)
{
	OmxPrint(OMX_TRACE, "msg prepare to deinit.\n");
    
	if (NULL == queue)
       {   
	    OmxPrint(OMX_FATAL, "%s: queue = NULL.\n", __func__);
	    return;
       }

	msg_stop(queue);

	kfree(queue->alloc);
	kfree(queue);
    
	OmxPrint(OMX_TRACE, "msg deinit ok.\n");
}

static HI_U32 msg_pending(msg_queue_s *queue)
{
	HI_U32 has_msg = 0;
	HI_U32 stopped = 0;
	unsigned long flags;

	if (NULL == queue)
       {   
	       OmxPrint(OMX_FATAL, "%s: queue = NULL.\n", __func__);
	       return -EINVAL;
       }

	spin_lock_irqsave(&queue->lock, flags);
	has_msg = !list_empty(&queue->head);
	stopped = queue->stop;
	spin_unlock_irqrestore(&queue->lock, flags);

	return has_msg || stopped;
}


HI_S32 msg_dequeue(msg_queue_s *queue, struct vdec_msginfo *pmsg_info)
{
	unsigned long flags;
	msg_data_s *msg = NULL;
	HI_S32 rc;
    
	if (NULL == queue || NULL == pmsg_info)
       {   
	       OmxPrint(OMX_FATAL, "%s: invalid param.\n", __func__);
	       return -EINVAL;
	}

	rc = wait_event_interruptible(queue->wait, msg_pending(queue));
	if (rc < 0) 
    {
        OmxPrint(OMX_INFO, "%s: wait msg failed.\n", __func__);
		return rc;
	}

	spin_lock_irqsave(&queue->lock, flags);
	if (!queue || queue->stop) 
       {
	       OmxPrint(OMX_WARN, "%s: msg queue stopped.\n", __func__);
		spin_unlock_irqrestore(&queue->lock, flags);
		return -ESHUTDOWN;
	}

	if (!list_empty(&queue->head)) 
       {
		msg = list_first_entry(&queue->head, msg_data_s, list);
		list_del(&msg->list);
		memcpy(pmsg_info, &msg->msg_info, sizeof(struct vdec_msginfo));
		list_add(&msg->list, &queue->free);
	}
	spin_unlock_irqrestore(&queue->lock, flags);
    
	return 0;
}



HI_S32  msg_queue(msg_queue_s *queue, HI_U32 msgcode, HI_U32 status, HI_VOID *priv)
{
	unsigned long flags;
	msg_data_s *msg;

	spin_lock_irqsave(&queue->lock, flags);
	if (queue->stop) 
       {
	       OmxPrint(OMX_FATAL, "%s: msg queue stopped.\n", __func__);
		spin_unlock_irqrestore(&queue->lock, flags);
		return 0;
	}

	if (list_empty(&queue->free)) 
       {
	       OmxPrint(OMX_FATAL, "%s: no free space in list.\n", __func__);
		spin_unlock_irqrestore(&queue->lock, flags);
		return -ENOMEM;
	}

	msg = list_first_entry(&queue->free, msg_data_s, list);
	list_del(&msg->list);
	msg->msg_info.status_code = status;
	msg->msg_info.msgcode = msgcode;

	if (priv)
       {
		memcpy(&msg->msg_info.msgdata, priv, sizeof(union vdec_msgdata));
	}

	list_add_tail(&msg->list, &queue->head);
	spin_unlock_irqrestore(&queue->lock, flags);

	wake_up(&queue->wait);

	return 0;
}
