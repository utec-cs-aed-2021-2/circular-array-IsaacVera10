#include "circulararray.h"

template <typename T>
class QueueArray : public CircularArray<T> { 
public:
    QueueArray(int capacity_):CircularArray<T>(capacity_);

};