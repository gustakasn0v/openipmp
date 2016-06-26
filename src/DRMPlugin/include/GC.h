/** \file GC.h

    Garbage collector.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (GC_H)
#define GC_H

/*! disabled warning
	  'identifier' : identifier was truncated to 'number' characters in
	  the debug information
*/
#pragma warning(disable: 4786)

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Exception used for garbage collector error.
*/
class GCException {
};

/*! \brief  Garbage collector.

    Counts number of references to an object and when it drops to zero,
    deletes the object. All classes that are to be garbage collected
    must inherit GC.
*/
class GC {
public:
  /*! \brief  Constructor.
  */
  GC(): refCount(0) {
  }

  /*! \brief  Destructor.
  */
  virtual ~GC() {
  	refCount = 0;
  }

  /*! \brief  Increase reference count.
  */
  void UpCount() {
  	refCount++;
  }

  /*! \brief  Decrease reference count.

      If reference count drops to zero, deletes the object.
  */
  void DwCount() {
	  if ((--refCount) == 0) {
		  delete this;
	  }
  }

private:
  //! Reference count.
	unsigned int refCount;
};

/*! \brief  Smart pointer to template type T.

    Template type T must inherit GC.

	  \warning  DO NOT CONSTRUCT SPtr<T> WITH ADDRESS OF LOCAL OBJECT OF TYPE T!
*/
template<typename T> class SPtr {
public:
  /*! \brief  Constructor.

      If pointer is not zero, increases reference count for it.

      \param  p         pointer to class T.
  */
	SPtr<T>(T* p = 0) {
		pointer = p; if (pointer != 0) pointer->UpCount();
	}

  /*! \brief  Copy constructor.

      If (smart) pointer is not zero, increases reference count for it.

      \param  rhs       smart pointer.
  */
	SPtr<T>(const SPtr<T>& rhs) {
		pointer = rhs.pointer; if (pointer != 0) pointer->UpCount();
	}

  /*! \brief  Destructor.

      If pointer is not zero, decreases reference count for it.
  */
	virtual ~SPtr<T>() {
		if (pointer != 0) pointer->DwCount(); pointer = 0;
	}

  /*! \brief  Cast to standard T* operator.
  */
	virtual operator T* () const {
		return pointer;
	}
/*
	template<class S> operator SPtr<S> () {
		return SPtr<S>(pointer);
	}
*/

  /*! \brief  Dereference operator.

      \returns  Reference to the object. If fails, throws GCException.
  */
  virtual T& operator * () const {
		if (pointer != 0) return (*pointer);
		throw GCException();
	}

  /*! \brief  Arrow operator.

      \returns  Standard pointer to the object. If fails, throws GCException.
  */
	virtual T* operator -> () const {
		if (pointer != 0) return pointer;
		throw GCException();
	}

  /*! \brief  Assignment operator.

      If rhs is not the same object as this one, decreases contained
      pointer reference count (if it is not zero), assigns rhs's pointer
      to contained pointer and increases contained pointer reference count
      (if it is not zero).

      \param  rhs         input, smart pointer.

      \returns  Smart pointer reference.
  */
  SPtr<T>& operator = (const SPtr<T>& rhs) {
		if (this != (&rhs)) {
			if (pointer != 0) pointer->DwCount();
			pointer = rhs.pointer;
			if (pointer != 0) pointer->UpCount();
		}
		return (*this);
	}

protected:
  //! Standard pointer.
	T* pointer;
};

/*! \brief  Non-zero smart pointer to template type T.

    Used to reduce checking of zero pointers.
    Template type T must inherit GC.

	  \warning  DO NOT CONSTRUCT NZSPtr<T> WITH ADDRESS OF LOCAL OBJECT OF TYPE T!
*/
template<typename T> class NZSPtr: public SPtr<T> {
public:
  /*! \brief  Constructor.

      If pointer is not zero, increases reference count for it.
      If fails (pointer is zero), throws GCException.

      \param  p         pointer to class T.
  */
	NZSPtr<T>(T* p): SPtr<T>(p) {
		if (p == 0) {
			throw GCException();
		}
	}

  /*! \brief  Constructor.

      If pointer is not zero, increases reference count for it.
      If fails (pointer is zero), throws GCException.

      \param  rhs       smart pointer.
  */
	NZSPtr<T>(const SPtr<T>& rhs): SPtr<T>(rhs) {
		if (rhs == 0) {
			throw GCException();
		}
	}

  /*! \brief  Copy constructor.

      Increases reference count for contained pointer.

      \param  rhs       smart pointer.
  */
	NZSPtr<T>(const NZSPtr<T>& rhs) {
		this->pointer = rhs.pointer; this->pointer->UpCount();
	}

  /*! \brief  Destructor.

      See SPtr<T>::~SPtr<T>.
  */
	virtual	~NZSPtr<T>() {
	}

  /*! \brief  Assignment operator.

      If rhs is not the same object as this one, decreases contained
      pointer reference count, assigns rhs's pointer to contained pointer
      and increases contained pointer reference count.

      \param  rhs         input, smart pointer.

      \returns  Smart pointer reference.
  */
  NZSPtr<T>& operator = (const NZSPtr<T>& rhs) {
		if (this != (&rhs)) {
			this->pointer->DwCount();
			this->pointer = rhs.pointer;
			this->pointer->UpCount();
		}
		return (*this);
	}

  /*! \brief  Less than operator.

      Tests whether contained object (dereferenced contained pointer)
      is less than rhs's contained object (dereferenced contained pointer).
      Assumes that type T has less than operator.

      \param  rhs         input, smart pointer.

      \returns  Boolean indicating whether contained object is less than
                rhs's contained object.
  */
  bool operator < (const NZSPtr<T>& rhs) const {
    return ((*(this->pointer)) < (*rhs));
	}
};

} // namespace DRMPlugin

#endif // !defined(GC_H)
