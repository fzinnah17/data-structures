#include "sequence1.h"
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;
using namespace weimin_csc212;
sequence1::sequence1() { used = 0; current_index = 0; }
void sequence1::start() { current_index = 0; }
void sequence1::advance()
{ if(current_index < used && is_item())
    current_index++; }
void sequence1::insert(const value_type& entry) {
    size_type i;
    assert(size() < CAPACITY);
    if (!is_item()) { current_index = 0; }
    for (i = used; i > current_index; i--) { data[i] = data[i - 1]; }
        data[current_index] = entry;
        used++;
}
void sequence1::attach(const value_type& entry) {
    size_type i;
    assert(size() < CAPACITY);
    if (!is_item()) { current_index = 0; }
    for (i = used; i > current_index; i--) { data[i] = data[i - 1]; }
    data[current_index+1] = entry;
    used++;
    current_index++;
}
void sequence1::remove_current() {
    if (!is_item())
            return;
        for (size_t i = current_index; i < used; i++)
            data[i] = data[i + 1];
        used--; }
sequence1::size_type sequence1::size() const
{
    return used;
}
bool sequence1::is_item() const
{ if (used != 0) return true;
    else return false; }
sequence1::value_type sequence1::current() const
{ assert(is_item());
    return data[current_index]; }
