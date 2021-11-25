#include "sequence2.h"
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;
using namespace assignment_sequence2;
    sequence::sequence()
    {
        current_ptr = NULL;
        head_ptr = NULL;
        tail_ptr = NULL;
        previous_ptr = NULL;
        many_nodes = 0;
    }
    sequence::sequence(const sequence &source)
    {
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        this->many_nodes = source.many_nodes;
        this->current_ptr = this->head_ptr;
        this->previous_ptr = NULL;
        node *curr = source.head_ptr;
        while (curr && curr != source.current_ptr)
        {
            curr = curr->link();
            previous_ptr = curr;
            current_ptr = current_ptr->link();
        }
    }
    sequence::~sequence()
    {
        list_clear(head_ptr);
    }
    void sequence::start()
    {
        current_ptr = head_ptr;
        previous_ptr = NULL;
    }
    void sequence::advance()
    {
        if (is_item())
        {
            this->previous_ptr = this->current_ptr;
            this->current_ptr = current_ptr->link();
        }
    }
    void sequence::insert(const value_type &entry)
    {
        if (!is_item())
        {
            list_head_insert(head_ptr, entry);
            previous_ptr = NULL;
            current_ptr = head_ptr;
        }
        else
        {
            if (current_ptr == head_ptr)
            {
                list_head_insert(head_ptr, entry);
                current_ptr = head_ptr;
                previous_ptr = NULL;
            }
            else
            {
                list_insert(previous_ptr, entry);
                current_ptr = previous_ptr->link();
            }
        }
        many_nodes++;
    }
    void sequence::attach(const value_type &entry)
    {
        if (is_item())
        {
            list_insert(current_ptr, entry);
            previous_ptr = current_ptr;
            current_ptr = current_ptr->link();
        }
        else
        {
            if (previous_ptr == NULL)
            {
                list_head_insert(head_ptr, entry);
                current_ptr = head_ptr;
                previous_ptr = NULL;
            }
            else
            {
                current_ptr = list_locate(head_ptr, list_length(head_ptr));
                list_insert(current_ptr, entry);
                current_ptr = current_ptr->link();
            }
        }

        many_nodes++;
    }
    void sequence::remove_current()
    {
        if (many_nodes >= 1)
        {
            if (current_ptr == head_ptr)
            {
                list_head_remove(head_ptr);
                current_ptr = head_ptr;
                previous_ptr = NULL;
            }
            else
            {
                current_ptr = current_ptr->link();
                list_remove(previous_ptr);
            }
            many_nodes--;
        }

    }
void sequence::operator=(const sequence &source)
  {
      if (this != &source)
      {
          list_clear(head_ptr);
          list_copy(source.head_ptr, head_ptr, tail_ptr);
          this->many_nodes = source.many_nodes;
          this->current_ptr = this->head_ptr;
          this->previous_ptr = NULL;
          node *curr = source.head_ptr;
          while (curr && curr != source.current_ptr)
          {
              curr = curr->link();
              previous_ptr = curr;
              current_ptr = current_ptr->link();
          }
      }
  }
    size_t sequence::size() const
    {
        return this->many_nodes;
    }
    bool sequence::is_item() const
    {
        return current_ptr != NULL && many_nodes > 0;
    }
    node::value_type sequence::current() const
    {
        if (is_item())
        {
            return current_ptr->data();
        }
        return value_type();
    }
