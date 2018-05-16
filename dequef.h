/***********************************************************************
 * Header:
 *    Deque
 * Summary:
 *    This class contains the notion of a Deque: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the Deque, set, Deque, Deque, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *        Deque         : A class that holds stuff
 *        DequeIterator : An interator through Deque
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef Deque_H
#define Deque_H

#include <cassert>

// forward declaration for DequeIterator
template <class T>
class DequeIterator;

/************************************************
 * Deque
 * A class that holds stuff
 ***********************************************/
template <class T>
class Deque
{
  public:
   // default constructor : empty and kinda useless
  Deque() : numItems(0), cap(0), data(NULL), first(0), last(0) {}

   // copy constructor : copy it
   Deque(const Deque & rhs) throw (const char *);

   // non-default constructor : pre-allocate
   Deque(int capacity) throw (const char *);

   // destructor : free everything
   ~Deque()        { if (cap) delete [] data; }

   // is the Deque currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the Deque
   void clear()        { numItems = 0; first = 0; last = 0; }

   // how many items are currently in the Deque?
   int size() const    { return numItems;              }

   Deque & operator= (const Deque & rhs) throw (const char *);

   int capacity() { return cap; }

   void resize();

   void push_back(const T & item) throw (const char *);

   void push_front(const T & item) throw (const char *);

   void pop_front() throw (const char *);

   void pop_back() throw (const char *);

   T & front() throw (const char *);

   T & back() throw (const char *);
  
  private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Deque?
   int cap;           // how many items can I put on the Deque before full?
   int first;
   int last;
};

/**************************************************
 * Deque ITERATOR
 * An iterator through Deque
 *************************************************/
template <class T>
class DequeIterator
{
  public:
   // default constructor
  DequeIterator() : p(NULL) {}

   // initialize to direct p to some item
  DequeIterator(T * p) : p(p) {}


   // not equals operator
   bool operator != (const DequeIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   DequeIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   DequeIterator <T> operator++(int postfix)
   {
      DequeIterator tmp(*this);
      p++;
      return tmp;
   }

  private:
   T * p;
};

/*******************************************
* Deque :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Deque <T> :: Deque(const Deque <T> & rhs) throw (const char *)
{
   data = NULL;
   first = last = cap = numItems = 0;
   *this = rhs; // calling assigment operator with right hand side
}

/**********************************************
 * Deque : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Deque to "capacity"
 **********************************************/
template <class T>
Deque <T> :: Deque(int capacity) throw (const char *)
{
   assert(capacity >= 0);

   first = 0;
   last = 0;

   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
       try
       {
          data = new T[capacity];
       }
       catch (std::bad_alloc)
       {
          throw "ERROR: Unable to allocate buffer";
       }


       // copy over the stuff
       this->cap = capacity;
       this->numItems = 0;

       // initialize the Deque by calling the default constructor
       for (int i = 0; i < capacity; i++)
          data[i] = T();
}

/***************************************************
 * Deque :: Assignment Operator
 * Copies Old data into new data
 **************************************************/
template <class T>
Deque <T> & Deque <T>  :: operator= (const Deque & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);

   // do nothing if there is nothing to do
   if (data != NULL)
   {
      delete [] data;
   }

   first = rhs.first;
   last = rhs.last;

   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = NULL;
      return *this;
   }

   // attempt to allocate
       try
   {
      data = new T[rhs.cap];
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < cap; i++)
      data[i] = rhs.data[i];

   return *this;
}

/***************************************************
 * Deque :: resize THAT
 * Doubles the size of the Deque
 **************************************************/
   template <class T>;
   void Deque <T> :: resize()
   {
      T * tempData = new T[cap *= 2];
      for (int i = 0; i < numItems; i++)
      {
         tempData[i] = data[first];
         first = (first + 1) % numItems;
      }

      first = 0;
      last = numItems;

      delete [] data;
      data = tempData;
   }

/***************************************************
 * Deque :: push_front
 * Moves elements in the array forward one
 **************************************************/
template <class T>
void Deque <T> :: push_front(const T & item) throw (const char *)
{
   if(cap == 0)
   {
      numItems = 0;
      cap = 1;
      data = new T[cap];
   }

   else if(cap == numItems)
   {
      resize();
   }

   first = first - 1;

   if(first <  0)
   {
      first = cap - 1;
   }


   data[first] = item;
//   first = (first + 1) % cap;
   numItems++;

}

/***************************************************
 * Deque :: push_back
 * Moves elements in the array forward one
 **************************************************/
template <class T>
void Deque <T> :: push_back(const T & item) throw (const char *)
{
   if(cap == 0)
   {
      numItems = 0;
      cap = 1;
      data = new T[cap];
   }

   else if(cap == numItems)
   {
      resize();
   }

   data[last] = item; // sotre item where last index is printing
   last = (last + 1) % cap; // increment and wrap last index
   numItems++;

}


/***************************************************
 * Deque :: pop_front
 * Removes an item from the end of the Deque
 **************************************************/
template <class T>
void Deque <T> :: pop_front() throw (const char *)
{
   if (!empty())
   {
      numItems--;
      first = (first + 1) % cap;
   }
   else
      throw "ERROR: unable to pop from the front of empty deque";

}

/***************************************************
 * Deque :: pop_back
 * Removes an item from the end of the Deque
 **************************************************/
template <class T>
void Deque <T> :: pop_back() throw (const char *)
{
   if (!empty())
   {
      numItems--;
      last = last - 1;

      if(last < 0)
         last = (last + 1) % cap;
   }
   
   else
      throw "ERROR: unable to pop from the back of empty deque";

    

}

/***************************************************
 * Deque :: front
 * Returns the item is currently at the top of
 * the Deque
 **************************************************/
template <class T>
T & Deque <T> :: front() throw (const char *)
{

   if (!empty())
      return data[first];
   else
      throw "ERROR: unable to access data from an empty deque";

}

/***************************************************
 * Deque :: back
 * Returns the item is currently at the end of Deque
 **************************************************/
template <class T>
T & Deque <T> :: back() throw (const char *)
{

   if (!empty())
   {
      if(last == 0)
         return data[cap - 1];
      else
         return data[last - 1];
   }
   else
      throw "ERROR: unable to access data from an empty deque";

}

#endif // Deque_H

