/**	\file Value.h

	 Templated finite and infinite values with comparation operators.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (VALUE_H)
#define VALUE_H

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Value of type T.
*/
template<typename T> class ITValue {
public:
  virtual ~ITValue<T>() {
  }
};

/*! \brief  Positive infinite value of type T.
*/
template<typename T> class IPosInfTValue {
public:
  virtual ~IPosInfTValue<T>() {
  }
};

/*! \brief  Negative infinite value of type T.
*/
template<typename T> class INegInfTValue {
public:
  virtual ~INegInfTValue<T>() {
  }
};

/*! \brief  Finite value of type T.
*/
template<typename T> class IFiniteTValue {
public:
  virtual ~IFiniteTValue<T>() {
  }

  /*! \brief  Get (finite) value.

      \returns  (Finite) value.
  */
  virtual const T& Get() const = 0;
};

/*! \brief  Value of type T with comparation operators.
*/
template<typename T> class TValue {
public:
  virtual ~TValue<T>() {
  }

  /*! \brief  Less than value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  virtual bool operator < (const TValue<T>& rhs) const = 0;

  /*! \brief  Equal to value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const TValue<T>& rhs) const = 0;

  /*! \brief  Less than or equal to value of type T operator.

      \returns Boolean indicating if this value is less than or equal rhs.
  */
  bool operator <= (const TValue<T>& rhs) const {
    return (((*this) < rhs) || ((*this) == rhs));
  }

  /*! \brief  Greater than value of type T operator.

      \returns Boolean indicating if this value is greater than rhs.
  */
  bool operator > (const TValue<T>& rhs) const {
    return (!((*this) <= rhs));
  }

  /*! \brief  Greater than or equal to value of type T operator.

      \returns Boolean indicating if this value is greater than or equal rhs.
  */
  bool operator >= (const TValue<T>& rhs) const {
    return (!((*this) < rhs));
  }

  /*! \brief  Less than finite value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  virtual bool operator < (const IFiniteTValue<T>& rhs) const = 0;

  /*! \brief  Equal to finite value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const IFiniteTValue<T>& rhs) const = 0;

  /*! \brief  Less than or equal to finite value of type T operator.

      \returns Boolean indicating if this value is less than or equal rhs.
  */
  bool operator <= (const IFiniteTValue<T>& rhs) const {
    return (((*this) < rhs) || ((*this) == rhs));
  }

  /*! \brief  Greater than finite value of type T operator.

      \returns Boolean indicating if this value is greater than rhs.
  */
  bool operator > (const IFiniteTValue<T>& rhs) const {
    return (!((*this) <= rhs));
  }

  /*! \brief  Greater than or equal to finite value of type T operator.

      \returns Boolean indicating if this value is greater than or equal rhs.
  */
  bool operator >= (const IFiniteTValue<T>& rhs) const {
    return (!((*this) < rhs));
  }

  /*! \brief  Less than positive infinite value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  virtual bool operator < (const IPosInfTValue<T>& rhs) const = 0;

  /*! \brief  Equal to positive infinite value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const IPosInfTValue<T>& rhs) const = 0;

  /*! \brief  Less than or equal to positive infinite value of type T operator.

      \returns Boolean indicating if this value is less than or equal rhs.
  */
  bool operator <= (const IPosInfTValue<T>& rhs) const {
    return (((*this) < rhs) || ((*this) == rhs));
  }

  /*! \brief  Greater than positive infinite value of type T operator.

      \returns Boolean indicating if this value is greater than rhs.
  */
  bool operator > (const IPosInfTValue<T>& rhs) const {
//    return (!((*this) <= rhs));
    return false;
  }

  /*! \brief  Greater than or equal to positive infinite value of type T operator.

      \returns Boolean indicating if this value is greater than or equal rhs.
  */
  bool operator >= (const IPosInfTValue<T>& rhs) const {
    return (!((*this) < rhs));
  }

  /*! \brief  Less than negative infinite value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  bool operator < (const INegInfTValue<T>& rhs) const {
    return false;
  }

  /*! \brief  Equal to negative infinite value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const INegInfTValue<T>& rhs) const = 0;

  /*! \brief  Less than or equal to negative infinite value of type T operator.

      \returns Boolean indicating if this value is less than or equal rhs.
  */
  bool operator <= (const INegInfTValue<T>& rhs) const {
    return (((*this) < rhs) || ((*this) == rhs));
  }

  /*! \brief  Greater than negative infinite value of type T operator.

      \returns Boolean indicating if this value is greater than rhs.
  */
  bool operator > (const INegInfTValue<T>& rhs) const {
    return (!((*this) <= rhs));
  }

  /*! \brief  Greater than or equal to negative infinite value of type T operator.

      \returns Boolean indicating if this value is greater than or equal rhs.
  */
  bool operator >= (const INegInfTValue<T>& rhs) const {
    return (!((*this) < rhs));
  }
};

/*! \brief  Positive infinite value of type T with comparation operators.
*/
template<typename T> class PosInfTValue: public IPosInfTValue<T>, public TValue<T> {
public:
  virtual ~PosInfTValue<T>() {
  }

  /*! \brief  Less than value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  virtual bool operator < (const TValue<T>& rhs) const {
    return (!(rhs >= (IPosInfTValue<T>&)(*this)));
  }

  /*! \brief  Equal to value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const TValue<T>& rhs) const {
    return (rhs == (IPosInfTValue<T>&)(*this));
  }

  /*! \brief  Less than finite value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  virtual bool operator < (const IFiniteTValue<T>& rhs) const {
    return false;
  }

  /*! \brief  Equal to finite value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const IFiniteTValue<T>& rhs) const {
    return false;
  }

  /*! \brief  Less than positive infinite value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  virtual bool operator < (const IPosInfTValue<T>& rhs) const {
    return false;
  }

  /*! \brief  Equal to positive infinite value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const IPosInfTValue<T>& rhs) const {
    return true;
  }

  /*! \brief  Equal to negative infinite value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const INegInfTValue<T>& rhs) const {
    return false;
  }
};

/*! \brief  Negative infinite value of type T with comparation operators.
*/
template<typename T> class NegInfTValue: public INegInfTValue<T>, public TValue<T> {
public:
  virtual ~NegInfTValue<T>() {
  }

  /*! \brief  Less than value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  virtual bool operator < (const TValue<T>& rhs) const {
    return (!(rhs >= (INegInfTValue<T>&)(*this)));
  }

  /*! \brief  Equal to value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const TValue<T>& rhs) const {
    return (rhs == (INegInfTValue<T>&)(*this));
  }

  /*! \brief  Less than finite value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  virtual bool operator < (const IFiniteTValue<T>& rhs) const {
    return true;
  }

  /*! \brief  Equal to finite value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const IFiniteTValue<T>& rhs) const {
    return false;
  }

  /*! \brief  Less than positive infinite value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  virtual bool operator < (const IPosInfTValue<T>& rhs) const {
    return true;
  }

  /*! \brief  Equal to positive infinite value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const IPosInfTValue<T>& rhs) const {
    return false;
  }

  /*! \brief  Equal to negative infinite value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const INegInfTValue<T>& rhs) const {
    return true;
  }
};

/*! \brief  Finite value of type T with comparation operators.
*/
template<typename T> class FiniteTValue: public IFiniteTValue<T>, public TValue<T> {
public:
  /*! \brief  Constructor.

      \param  val       value of type T.
  */
  FiniteTValue(const T& val): tval(val) {
  }

  virtual ~FiniteTValue<T>() {
  }

  /*! \brief  Get finite value.

      \returns Finite value.
  */
  virtual const T& Get() const {
    return tval;
  }

  /*! \brief  Less than value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  virtual bool operator < (const TValue<T>& rhs) const {
    return (rhs >= (IFiniteTValue<T>&)(*this));
  }

  /*! \brief  Equal to value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const TValue<T>& rhs) const {
    return (rhs == (IFiniteTValue<T>&)(*this));
  }

  /*! \brief  Less than finite value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  virtual bool operator < (const IFiniteTValue<T>& rhs) const {
    return (Get() < rhs.Get());
  }

  /*! \brief  Equal to finite value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const IFiniteTValue<T>& rhs) const {
    return (Get() == rhs.Get());
  }

  /*! \brief  Less than positive infinite value of type T operator.

      \returns Boolean indicating if this value is less than rhs.
  */
  virtual bool operator < (const IPosInfTValue<T>& rhs) const {
    return true;
  }

  /*! \brief  Equal to positive infinite value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const IPosInfTValue<T>& rhs) const {
    return false;
  }

  /*! \brief  Equal to negative infinite value of type T operator.

      \returns Boolean indicating if this value is equal rhs.
  */
  virtual bool operator == (const INegInfTValue<T>& rhs) const {
    return false;
  }

private:
  T tval;
};

} // namespace DRMPlugin

#endif // !defined (VALUE_H)
