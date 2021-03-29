//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Martin Zmitko <xzmitk01@stud.fit.vutbr.cz>
// $Date:       $2021-02-22
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Zmitko
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()
{
    if(m_pHead == NULL) return;
    Element_t *next = m_pHead;
    while(next->pNext != NULL){
        Element_t *nextElement = next->pNext;
        delete(next);
        next = nextElement;
    }
}

void PriorityQueue::Insert(int value)
{
    Element_t* pElement = new Element_t {value, NULL};
    if(m_pHead == NULL){
        m_pHead = pElement;
    }
    else{
        Element_t *element = m_pHead, *lastElement = NULL;
        while(true){
            if(element->value < value){
                if(lastElement == NULL){
                    pElement->pNext = m_pHead;
                    m_pHead = pElement;
                } 
                else{
                    pElement->pNext = element;
                    lastElement->pNext = pElement;
                } 
                return;
            }
            if(element->pNext == NULL) break;
            lastElement = element;
            element = element->pNext;
        }
        element->pNext = pElement;
    }
}

bool PriorityQueue::Remove(int value)
{
    Element_t *element = m_pHead, *lastElement = NULL;
    while(element != NULL){
        if(element->value == value){
            if(lastElement == NULL) 
                m_pHead = element->pNext;
            else 
                lastElement->pNext = element->pNext;
            delete(element);
            return true;
        }
        
        lastElement = element;
        element = element->pNext;
    }
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t *element = m_pHead;
    while(element != NULL){
        if(element->value == value) return element;
        element = element->pNext;
    } 
    return NULL;
}

size_t PriorityQueue::Length()
{
	size_t length = 0;
    Element_t *next = m_pHead;
    while(next != NULL){
        length++;
        next = next->pNext;
    }
    return length;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
