/*
 *   This file is part of mGNCS4Touch, a component for MiniGUI.
 * 
 *   Copyright (C) 2008~2018, Beijing FMSoft Technologies Co., Ltd.
 * 
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 * 
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 * 
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *   Or,
 * 
 *   As this program is a library, any link to this program must follow
 *   GNU General Public License version 3 (GPLv3). If you cannot accept
 *   GPLv3, you need to be licensed from FMSoft.
 * 
 *   If you have got a commercial license of this program, please use it
 *   under the terms and conditions of the commercial license.
 * 
 *   For more information about the commercial license, please refer to
 *   <http://www.minigui.com/en/about/licensing-policy/>.
 */
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgplus/mgplus.h>
#include <mgeff/mgeff.h>
#include <mgncs/mgncs.h>

#include "mgncs4touch.h"

#define ITEM_HEAD(ptr) list_entry(ptr, mPieceItem, list)

static void mGroupItemIterator_construct(mGroupItemIterator *self, DWORD add_data)
{
	Class(mItemIterator).construct((mItemIterator*)self, add_data);
    self->current = self->head = NULL;
    self->parent = NULL;
    self->manager = NULL;
    self->key = (char*)add_data;

    self->parentIter = NULL;
    self->childIter = NULL;
}

static void mGroupItemIterator_destroy(mGroupItemIterator *self)
{
    Class(mItemIterator).destroy((mItemIterator*)self);
    if (self->parentIter) {
        DELETE(self->parentIter);
    }
    if (self->childIter) {
        DELETE(self->childIter);
    }
}

static mPieceItem*  mGroupItemIterator_next(mGroupItemIterator* self)
{
    mPieceItem* item = NULL;

    if (self->childIter == NULL) {
        if ((item = _c(self->parentIter)->next(self->parentIter))) {
            self->childIter = (mListItemIterator*)NEW(mListItemIterator);
            self->childIter->current = self->childIter->head = &((mGroupPieceItem*)item)->child;
            self->manager = (mAbstractItemManager*)self->parentIter->manager;
        }
    }
    else {
        item = _c(self->childIter)->next(self->childIter);
        if (item == NULL)  {
            DELETE(self->childIter);
            self->childIter = NULL;
            if ((item = _c(self->parentIter)->next(self->parentIter))) {
                self->childIter = (mListItemIterator*)NEW(mListItemIterator);
                self->childIter->current = self->childIter->head = &((mGroupPieceItem*)item)->child;
                self->manager = (mAbstractItemManager*)self->parentIter->manager;
            }
        }
    }
    return item;
}

static mPieceItem*  mGroupItemIterator_prev(mGroupItemIterator* self)
{
    mPieceItem* item = NULL;

    if (self->childIter == NULL) {
        if ((item = _c(self->parentIter)->prev(self->parentIter))) {
            self->childIter = (mListItemIterator*)NEW(mListItemIterator);
            self->childIter->current = self->childIter->head = &((mGroupPieceItem*)item)->child;
            self->manager = (mAbstractItemManager*)self->parentIter->manager;
        }
    }
    else {
        item = _c(self->childIter)->prev(self->childIter);
        if (item == NULL)  {
            DELETE(self->childIter);
            self->childIter = NULL;
            if ((item = _c(self->parentIter)->prev(self->parentIter))) {
                self->childIter = (mListItemIterator*)NEW(mListItemIterator);
                self->childIter->current = self->childIter->head = &((mGroupPieceItem*)item)->child;
                self->manager = (mAbstractItemManager*)self->parentIter->manager;
            }
        }
    }
    return item;
}

static mGroupItemIterator* mGroupItemIterator_duplicate(mGroupItemIterator* self)
{
    mGroupItemIterator* iter = (mGroupItemIterator*)NEWEX(mGroupItemIterator, (DWORD)self->key);
    if (NULL != iter) {
        iter->parentIter = (mListItemIterator*)_c(self->parentIter)->duplicate(self->parentIter);
        if (self->childIter) {
            iter->childIter = (mListItemIterator*)_c(self->childIter)->duplicate(self->childIter);
        }
        iter->manager = (mAbstractItemManager*)self->manager;
        return iter;
    }
    return NULL;
}

BEGIN_MINI_CLASS(mGroupItemIterator, mItemIterator)
	CLASS_METHOD_MAP(mGroupItemIterator, construct)
	CLASS_METHOD_MAP(mGroupItemIterator, destroy)
	CLASS_METHOD_MAP(mGroupItemIterator, next)
	CLASS_METHOD_MAP(mGroupItemIterator, prev)
	CLASS_METHOD_MAP(mGroupItemIterator, duplicate)
END_MINI_CLASS
