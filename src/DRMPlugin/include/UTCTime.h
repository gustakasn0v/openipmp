/** \file UTCTime.h

    UTC time implementation.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (UTCTIME_H)
#define UTCTIME_H

#include <string>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Class used for UTC time representation error.
*/
class UTCTimeException {
};

/*! \brief  UTC time.
*/
class UTCTime {
public:
  /*! \brief  Constructor.

      \param  val       value.

      If fails, throws UTCTimeException.
  */
  UTCTime(const std::string& val): value(val) {
    if (value.size() != 20) {
      throw UTCTimeException();
    }
    char* vv = (char*)(value.data());
    if ((vv[4] != '-') || (vv[7] != '-') || (vv[10] != 'T') || (vv[13] != ':') ||
        (vv[16] != ':') || (vv[19] != 'Z')) {
      throw UTCTimeException();
    }
  }

  /*! \brief  Copy constructor.

      \param  rhs       UTC time.
  */
  UTCTime(const UTCTime& rhs): value(rhs.value) {
  }

  /*! \brief  Less than operator.

      \param  rhs       input, UTC time.

      \returns  Boolean indicating if this time is less than rhs.
  */
  bool operator < (const UTCTime& rhs) const {
    return (value < rhs.value);
  }

  /*! \brief  Equal to operator.

      \param  rhs       input, UTC time.

      \returns  Boolean indicating if this time is equal rhs.
  */
  bool operator == (const UTCTime& rhs) const {
    return (value == rhs.value);
  }

  /*! \brief  Less than or equal to operator.

      \param  rhs       input, UTC time.

      \returns  Boolean indicating if this time is less than or equal rhs.
  */
  bool operator <= (const UTCTime& rhs) const {
    return (value <= rhs.value);
  }

  /*! \brief  Get time value.

      \returns  Time value.
  */
  const std::string& Get() const {
    return value;
  }

private:
  std::string value;
};

} // namespace DRMPlugin

#endif // !defined (UTCTIME_H)
