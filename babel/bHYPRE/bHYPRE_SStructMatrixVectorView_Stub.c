/*
 * File:          bHYPRE_SStructMatrixVectorView_Stub.c
 * Symbol:        bHYPRE.SStructMatrixVectorView-v1.0.0
 * Symbol Type:   interface
 * Babel Version: 0.10.12
 * Description:   Client-side glue code for bHYPRE.SStructMatrixVectorView
 * 
 * WARNING: Automatically generated; changes will be lost
 * 
 * babel-version = 0.10.12
 */

#include "bHYPRE_SStructMatrixVectorView.h"
#include "bHYPRE_SStructMatrixVectorView_IOR.h"
#ifndef included_sidl_interface_IOR_h
#include "sidl_interface_IOR.h"
#endif
#ifndef included_sidl_rmi_InstanceHandle_h
#include "sidl_rmi_InstanceHandle.h"
#endif
#ifndef included_sidl_rmi_ConnectRegistry_h
#include "sidl_rmi_ConnectRegistry.h"
#endif
#ifndef included_sidl_interface_IOR_h
#include "sidl_interface_IOR.h"
#endif
#include <stddef.h>
#include <string.h>
#include "sidl_BaseInterface_IOR.h"
#include "babel_config.h"
#ifdef SIDL_DYNAMIC_LIBRARY
#include <stdio.h>
#include <stdlib.h>
#include "sidl_Loader.h"
#endif

/*
 * connect_loaded is a boolean value showing if the IHConnect for this object has been loaded into the connectRegistry
 */

static int connect_loaded = 0;

static struct bHYPRE_SStructMatrixVectorView__object* 
  bHYPRE_SStructMatrixVectorView__remoteConnect(const char* url,
  sidl_BaseInterface *_ex);
static struct bHYPRE_SStructMatrixVectorView__object* 
  bHYPRE_SStructMatrixVectorView__IHConnect(sidl_rmi_InstanceHandle instance,
  sidl_BaseInterface *_ex);
/*
 * RMI connector function for the class.
 */

bHYPRE_SStructMatrixVectorView
bHYPRE_SStructMatrixVectorView__connect(const char* url,
  sidl_BaseInterface *_ex)
{
  return bHYPRE_SStructMatrixVectorView__remoteConnect(url, _ex);
}

/*
 * <p>
 * Add one to the intrinsic reference count in the underlying object.
 * Object in <code>sidl</code> have an intrinsic reference count.
 * Objects continue to exist as long as the reference count is
 * positive. Clients should call this method whenever they
 * create another ongoing reference to an object or interface.
 * </p>
 * <p>
 * This does not have a return value because there is no language
 * independent type that can refer to an interface or a
 * class.
 * </p>
 */

void
bHYPRE_SStructMatrixVectorView_addRef(
  /* in */ bHYPRE_SStructMatrixVectorView self)
{
  (*self->d_epv->f_addRef)(
    self->d_object);
}

/*
 * Decrease by one the intrinsic reference count in the underlying
 * object, and delete the object if the reference is non-positive.
 * Objects in <code>sidl</code> have an intrinsic reference count.
 * Clients should call this method whenever they remove a
 * reference to an object or interface.
 */

void
bHYPRE_SStructMatrixVectorView_deleteRef(
  /* in */ bHYPRE_SStructMatrixVectorView self)
{
  (*self->d_epv->f_deleteRef)(
    self->d_object);
}

/*
 * Return true if and only if <code>obj</code> refers to the same
 * object as this object.
 */

sidl_bool
bHYPRE_SStructMatrixVectorView_isSame(
  /* in */ bHYPRE_SStructMatrixVectorView self,
  /* in */ sidl_BaseInterface iobj)
{
  return (*self->d_epv->f_isSame)(
    self->d_object,
    iobj);
}

/*
 * Check whether the object can support the specified interface or
 * class.  If the <code>sidl</code> type name in <code>name</code>
 * is supported, then a reference to that object is returned with the
 * reference count incremented.  The callee will be responsible for
 * calling <code>deleteRef</code> on the returned object.  If
 * the specified type is not supported, then a null reference is
 * returned.
 */

sidl_BaseInterface
bHYPRE_SStructMatrixVectorView_queryInt(
  /* in */ bHYPRE_SStructMatrixVectorView self,
  /* in */ const char* name)
{
  return (*self->d_epv->f_queryInt)(
    self->d_object,
    name);
}

/*
 * Return whether this object is an instance of the specified type.
 * The string name must be the <code>sidl</code> type name.  This
 * routine will return <code>true</code> if and only if a cast to
 * the string type name would succeed.
 */

sidl_bool
bHYPRE_SStructMatrixVectorView_isType(
  /* in */ bHYPRE_SStructMatrixVectorView self,
  /* in */ const char* name)
{
  return (*self->d_epv->f_isType)(
    self->d_object,
    name);
}

/*
 * Return the meta-data about the class implementing this interface.
 */

sidl_ClassInfo
bHYPRE_SStructMatrixVectorView_getClassInfo(
  /* in */ bHYPRE_SStructMatrixVectorView self)
{
  return (*self->d_epv->f_getClassInfo)(
    self->d_object);
}

/*
 * Set the MPI Communicator.  DEPRECATED, Use Create()
 * 
 */

int32_t
bHYPRE_SStructMatrixVectorView_SetCommunicator(
  /* in */ bHYPRE_SStructMatrixVectorView self,
  /* in */ bHYPRE_MPICommunicator mpi_comm)
{
  return (*self->d_epv->f_SetCommunicator)(
    self->d_object,
    mpi_comm);
}

/*
 * Prepare an object for setting coefficient values, whether for
 * the first time or subsequently.
 * 
 */

int32_t
bHYPRE_SStructMatrixVectorView_Initialize(
  /* in */ bHYPRE_SStructMatrixVectorView self)
{
  return (*self->d_epv->f_Initialize)(
    self->d_object);
}

/*
 * Finalize the construction of an object before using, either
 * for the first time or on subsequent uses. {\tt Initialize}
 * and {\tt Assemble} always appear in a matched set, with
 * Initialize preceding Assemble. Values can only be set in
 * between a call to Initialize and Assemble.
 * 
 */

int32_t
bHYPRE_SStructMatrixVectorView_Assemble(
  /* in */ bHYPRE_SStructMatrixVectorView self)
{
  return (*self->d_epv->f_Assemble)(
    self->d_object);
}

/*
 *  A semi-structured matrix or vector contains a Struct or IJ matrix
 *  or vector.  GetObject returns it.
 * The returned type is a sidl.BaseInterface.
 * QueryInterface or Cast must be used on the returned object to
 * convert it into a known type.
 * 
 */

int32_t
bHYPRE_SStructMatrixVectorView_GetObject(
  /* in */ bHYPRE_SStructMatrixVectorView self,
  /* out */ sidl_BaseInterface* A)
{
  return (*self->d_epv->f_GetObject)(
    self->d_object,
    A);
}

/*
 * Cast method for interface and class type conversions.
 */

bHYPRE_SStructMatrixVectorView
bHYPRE_SStructMatrixVectorView__cast(
  void* obj)
{
  bHYPRE_SStructMatrixVectorView cast = NULL;

  if(!connect_loaded) {
    sidl_rmi_ConnectRegistry_registerConnect("bHYPRE.SStructMatrixVectorView",
      (void*)bHYPRE_SStructMatrixVectorView__IHConnect);
    connect_loaded = 1;
  }
  if (obj != NULL) {
    sidl_BaseInterface base = (sidl_BaseInterface) obj;
    cast = (bHYPRE_SStructMatrixVectorView) (*base->d_epv->f__cast)(
      base->d_object,
      "bHYPRE.SStructMatrixVectorView");
  }

  return cast;
}

/*
 * String cast method for interface and class type conversions.
 */

void*
bHYPRE_SStructMatrixVectorView__cast2(
  void* obj,
  const char* type)
{
  void* cast = NULL;

  if (obj != NULL) {
    sidl_BaseInterface base = (sidl_BaseInterface) obj;
    cast = (*base->d_epv->f__cast)(base->d_object, type);
  }

  return cast;
}
/*
 * Select and execute a method by name
 */

void
bHYPRE_SStructMatrixVectorView__exec(
  /* in */ bHYPRE_SStructMatrixVectorView self,
  /* in */ const char* methodName,
  /* in */ sidl_io_Deserializer inArgs,
  /* in */ sidl_io_Serializer outArgs)
{
  (*self->d_epv->f__exec)(
  self->d_object,
  methodName,
  inArgs,
  outArgs);
}

/*
 * Get the URL of the Implementation of this object (for RMI)
 */

char*
bHYPRE_SStructMatrixVectorView__getURL(
  /* in */ bHYPRE_SStructMatrixVectorView self)
{
  return (*self->d_epv->f__getURL)(
  self->d_object);
}

struct bHYPRE_SStructMatrixVectorView__array*
bHYPRE_SStructMatrixVectorView__array_createCol(
  int32_t       dimen,
  const int32_t lower[],
  const int32_t upper[])
{
  return (struct 
    bHYPRE_SStructMatrixVectorView__array*)sidl_interface__array_createCol(
    dimen, lower, upper);
}

struct bHYPRE_SStructMatrixVectorView__array*
bHYPRE_SStructMatrixVectorView__array_createRow(
  int32_t       dimen,
  const int32_t lower[],
  const int32_t upper[])
{
  return (struct 
    bHYPRE_SStructMatrixVectorView__array*)sidl_interface__array_createRow(
    dimen, lower, upper);
}

struct bHYPRE_SStructMatrixVectorView__array*
bHYPRE_SStructMatrixVectorView__array_create1d(int32_t len)
{
  return (struct 
    bHYPRE_SStructMatrixVectorView__array*)sidl_interface__array_create1d(len);
}

struct bHYPRE_SStructMatrixVectorView__array*
bHYPRE_SStructMatrixVectorView__array_create1dInit(
  int32_t len, 
  bHYPRE_SStructMatrixVectorView* data)
{
  return (struct 
    bHYPRE_SStructMatrixVectorView__array*)sidl_interface__array_create1dInit(
    len, (struct sidl_BaseInterface__object **)data);
}

struct bHYPRE_SStructMatrixVectorView__array*
bHYPRE_SStructMatrixVectorView__array_create2dCol(int32_t m, int32_t n)
{
  return (struct 
    bHYPRE_SStructMatrixVectorView__array*)sidl_interface__array_create2dCol(m,
    n);
}

struct bHYPRE_SStructMatrixVectorView__array*
bHYPRE_SStructMatrixVectorView__array_create2dRow(int32_t m, int32_t n)
{
  return (struct 
    bHYPRE_SStructMatrixVectorView__array*)sidl_interface__array_create2dRow(m,
    n);
}

struct bHYPRE_SStructMatrixVectorView__array*
bHYPRE_SStructMatrixVectorView__array_borrow(
  bHYPRE_SStructMatrixVectorView* firstElement,
  int32_t       dimen,
  const int32_t lower[],
  const int32_t upper[],
  const int32_t stride[])
{
  return (struct 
    bHYPRE_SStructMatrixVectorView__array*)sidl_interface__array_borrow(
    (struct sidl_BaseInterface__object **)
    firstElement, dimen, lower, upper, stride);
}

struct bHYPRE_SStructMatrixVectorView__array*
bHYPRE_SStructMatrixVectorView__array_smartCopy(
  struct bHYPRE_SStructMatrixVectorView__array *array)
{
  return (struct bHYPRE_SStructMatrixVectorView__array*)
    sidl_interface__array_smartCopy((struct sidl_interface__array *)array);
}

void
bHYPRE_SStructMatrixVectorView__array_addRef(
  struct bHYPRE_SStructMatrixVectorView__array* array)
{
  sidl_interface__array_addRef((struct sidl_interface__array *)array);
}

void
bHYPRE_SStructMatrixVectorView__array_deleteRef(
  struct bHYPRE_SStructMatrixVectorView__array* array)
{
  sidl_interface__array_deleteRef((struct sidl_interface__array *)array);
}

bHYPRE_SStructMatrixVectorView
bHYPRE_SStructMatrixVectorView__array_get1(
  const struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1)
{
  return (bHYPRE_SStructMatrixVectorView)
    sidl_interface__array_get1((const struct sidl_interface__array *)array
    , i1);
}

bHYPRE_SStructMatrixVectorView
bHYPRE_SStructMatrixVectorView__array_get2(
  const struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  const int32_t i2)
{
  return (bHYPRE_SStructMatrixVectorView)
    sidl_interface__array_get2((const struct sidl_interface__array *)array
    , i1, i2);
}

bHYPRE_SStructMatrixVectorView
bHYPRE_SStructMatrixVectorView__array_get3(
  const struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3)
{
  return (bHYPRE_SStructMatrixVectorView)
    sidl_interface__array_get3((const struct sidl_interface__array *)array
    , i1, i2, i3);
}

bHYPRE_SStructMatrixVectorView
bHYPRE_SStructMatrixVectorView__array_get4(
  const struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4)
{
  return (bHYPRE_SStructMatrixVectorView)
    sidl_interface__array_get4((const struct sidl_interface__array *)array
    , i1, i2, i3, i4);
}

bHYPRE_SStructMatrixVectorView
bHYPRE_SStructMatrixVectorView__array_get5(
  const struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  const int32_t i5)
{
  return (bHYPRE_SStructMatrixVectorView)
    sidl_interface__array_get5((const struct sidl_interface__array *)array
    , i1, i2, i3, i4, i5);
}

bHYPRE_SStructMatrixVectorView
bHYPRE_SStructMatrixVectorView__array_get6(
  const struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  const int32_t i5,
  const int32_t i6)
{
  return (bHYPRE_SStructMatrixVectorView)
    sidl_interface__array_get6((const struct sidl_interface__array *)array
    , i1, i2, i3, i4, i5, i6);
}

bHYPRE_SStructMatrixVectorView
bHYPRE_SStructMatrixVectorView__array_get7(
  const struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  const int32_t i5,
  const int32_t i6,
  const int32_t i7)
{
  return (bHYPRE_SStructMatrixVectorView)
    sidl_interface__array_get7((const struct sidl_interface__array *)array
    , i1, i2, i3, i4, i5, i6, i7);
}

bHYPRE_SStructMatrixVectorView
bHYPRE_SStructMatrixVectorView__array_get(
  const struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t indices[])
{
  return (bHYPRE_SStructMatrixVectorView)
    sidl_interface__array_get((const struct sidl_interface__array *)array,
      indices);
}

void
bHYPRE_SStructMatrixVectorView__array_set1(
  struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  bHYPRE_SStructMatrixVectorView const value)
{
  sidl_interface__array_set1((struct sidl_interface__array *)array
  , i1, (struct sidl_BaseInterface__object *)value);
}

void
bHYPRE_SStructMatrixVectorView__array_set2(
  struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  const int32_t i2,
  bHYPRE_SStructMatrixVectorView const value)
{
  sidl_interface__array_set2((struct sidl_interface__array *)array
  , i1, i2, (struct sidl_BaseInterface__object *)value);
}

void
bHYPRE_SStructMatrixVectorView__array_set3(
  struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  bHYPRE_SStructMatrixVectorView const value)
{
  sidl_interface__array_set3((struct sidl_interface__array *)array
  , i1, i2, i3, (struct sidl_BaseInterface__object *)value);
}

void
bHYPRE_SStructMatrixVectorView__array_set4(
  struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  bHYPRE_SStructMatrixVectorView const value)
{
  sidl_interface__array_set4((struct sidl_interface__array *)array
  , i1, i2, i3, i4, (struct sidl_BaseInterface__object *)value);
}

void
bHYPRE_SStructMatrixVectorView__array_set5(
  struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  const int32_t i5,
  bHYPRE_SStructMatrixVectorView const value)
{
  sidl_interface__array_set5((struct sidl_interface__array *)array
  , i1, i2, i3, i4, i5, (struct sidl_BaseInterface__object *)value);
}

void
bHYPRE_SStructMatrixVectorView__array_set6(
  struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  const int32_t i5,
  const int32_t i6,
  bHYPRE_SStructMatrixVectorView const value)
{
  sidl_interface__array_set6((struct sidl_interface__array *)array
  , i1, i2, i3, i4, i5, i6, (struct sidl_BaseInterface__object *)value);
}

void
bHYPRE_SStructMatrixVectorView__array_set7(
  struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  const int32_t i5,
  const int32_t i6,
  const int32_t i7,
  bHYPRE_SStructMatrixVectorView const value)
{
  sidl_interface__array_set7((struct sidl_interface__array *)array
  , i1, i2, i3, i4, i5, i6, i7, (struct sidl_BaseInterface__object *)value);
}

void
bHYPRE_SStructMatrixVectorView__array_set(
  struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t indices[],
  bHYPRE_SStructMatrixVectorView const value)
{
  sidl_interface__array_set((struct sidl_interface__array *)array, indices,
    (struct sidl_BaseInterface__object *)value);
}

int32_t
bHYPRE_SStructMatrixVectorView__array_dimen(
  const struct bHYPRE_SStructMatrixVectorView__array* array)
{
  return sidl_interface__array_dimen((struct sidl_interface__array *)array);
}

int32_t
bHYPRE_SStructMatrixVectorView__array_lower(
  const struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t ind)
{
  return sidl_interface__array_lower((struct sidl_interface__array *)array,
    ind);
}

int32_t
bHYPRE_SStructMatrixVectorView__array_upper(
  const struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t ind)
{
  return sidl_interface__array_upper((struct sidl_interface__array *)array,
    ind);
}

int32_t
bHYPRE_SStructMatrixVectorView__array_length(
  const struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t ind)
{
  return sidl_interface__array_length((struct sidl_interface__array *)array,
    ind);
}

int32_t
bHYPRE_SStructMatrixVectorView__array_stride(
  const struct bHYPRE_SStructMatrixVectorView__array* array,
  const int32_t ind)
{
  return sidl_interface__array_stride((struct sidl_interface__array *)array,
    ind);
}

int
bHYPRE_SStructMatrixVectorView__array_isColumnOrder(
  const struct bHYPRE_SStructMatrixVectorView__array* array)
{
  return sidl_interface__array_isColumnOrder((struct sidl_interface__array 
    *)array);
}

int
bHYPRE_SStructMatrixVectorView__array_isRowOrder(
  const struct bHYPRE_SStructMatrixVectorView__array* array)
{
  return sidl_interface__array_isRowOrder((struct sidl_interface__array 
    *)array);
}

void
bHYPRE_SStructMatrixVectorView__array_copy(
  const struct bHYPRE_SStructMatrixVectorView__array* src,
  struct bHYPRE_SStructMatrixVectorView__array* dest)
{
  sidl_interface__array_copy((const struct sidl_interface__array *)src,
                             (struct sidl_interface__array *)dest);
}

struct bHYPRE_SStructMatrixVectorView__array*
bHYPRE_SStructMatrixVectorView__array_slice(
  struct bHYPRE_SStructMatrixVectorView__array* src,
  int32_t        dimen,
  const int32_t  numElem[],
  const int32_t  *srcStart,
  const int32_t  *srcStride,
  const int32_t  *newStart)
{
  return (struct bHYPRE_SStructMatrixVectorView__array*)
    sidl_interface__array_slice((struct sidl_interface__array *)src,
                                dimen, numElem, srcStart, srcStride, newStart);
}

struct bHYPRE_SStructMatrixVectorView__array*
bHYPRE_SStructMatrixVectorView__array_ensure(
  struct bHYPRE_SStructMatrixVectorView__array* src,
  int32_t dimen,
  int     ordering)
{
  return (struct bHYPRE_SStructMatrixVectorView__array*)
    sidl_interface__array_ensure((struct sidl_interface__array *)src, dimen,
      ordering);
}

#include <stdlib.h>
#include <string.h>
#include "sidl_rmi_ProtocolFactory.h"
#include "sidl_rmi_InstanceHandle.h"
#include "sidl_rmi_Invocation.h"
#include "sidl_rmi_Response.h"

#ifndef NULL
#define NULL 0
#endif

#include "sidl_thread.h"
#ifdef HAVE_PTHREAD
static struct sidl_recursive_mutex_t bHYPRE__SStructMatrixVectorView__mutex= SIDL_RECURSIVE_MUTEX_INITIALIZER;
#define LOCK_STATIC_GLOBALS sidl_recursive_mutex_lock( &bHYPRE__SStructMatrixVectorView__mutex )
#define UNLOCK_STATIC_GLOBALS sidl_recursive_mutex_unlock( &bHYPRE__SStructMatrixVectorView__mutex )
/* #define HAVE_LOCKED_STATIC_GLOBALS (sidl_recursive_mutex_trylock( &bHYPRE__SStructMatrixVectorView__mutex )==EDEADLOCK) */
#else
#define LOCK_STATIC_GLOBALS
#define UNLOCK_STATIC_GLOBALS
/* #define HAVE_LOCKED_STATIC_GLOBALS (1) */
#endif

/* Static variables to hold version of IOR */
static const int32_t s_IOR_MAJOR_VERSION = 0;
static const int32_t s_IOR_MINOR_VERSION = 9;

/* Static variables for managing EPV initialization. */
static int s_remote_initialized = 0;

static struct bHYPRE__SStructMatrixVectorView__epv 
  s_rem_epv__bhypre__sstructmatrixvectorview;

static struct bHYPRE_MatrixVectorView__epv s_rem_epv__bhypre_matrixvectorview;

static struct bHYPRE_ProblemDefinition__epv s_rem_epv__bhypre_problemdefinition;

static struct bHYPRE_SStructMatrixVectorView__epv 
  s_rem_epv__bhypre_sstructmatrixvectorview;

static struct sidl_BaseInterface__epv s_rem_epv__sidl_baseinterface;

/* REMOTE CAST: dynamic type casting for remote objects. */
static void* remote_bHYPRE__SStructMatrixVectorView__cast(
struct bHYPRE__SStructMatrixVectorView__object* self,
const char* name)
{
  void* cast = NULL;

  struct bHYPRE__SStructMatrixVectorView__object* s0;
   s0 =                                          self;

  if (!strcmp(name, "bHYPRE._SStructMatrixVectorView")) {
    cast = (void*) s0;
  } else if (!strcmp(name, "bHYPRE.MatrixVectorView")) {
    cast = (void*) &s0->d_bhypre_matrixvectorview;
  } else if (!strcmp(name, "bHYPRE.ProblemDefinition")) {
    cast = (void*) &s0->d_bhypre_problemdefinition;
  } else if (!strcmp(name, "bHYPRE.SStructMatrixVectorView")) {
    cast = (void*) &s0->d_bhypre_sstructmatrixvectorview;
  } else if (!strcmp(name, "sidl.BaseInterface")) {
    cast = (void*) &s0->d_sidl_baseinterface;
  }
  else if ((*self->d_epv->f_isType)(self,name)) {
    void* (*func)(sidl_rmi_InstanceHandle) = 
      (void* (*)(sidl_rmi_InstanceHandle)) 
      sidl_rmi_ConnectRegistry_getConnect(name);
    cast =  (*func)((sidl_rmi_InstanceHandle)self->d_data);
  }

  return cast;
}

/* REMOTE DELETE: call the remote destructor for the object. */
static void remote_bHYPRE__SStructMatrixVectorView__delete(
  struct bHYPRE__SStructMatrixVectorView__object* self)
{
  free((void*) self);
}

/* REMOTE GETURL: call the getURL function for the object. */
static char* remote_bHYPRE__SStructMatrixVectorView__getURL(
  struct bHYPRE__SStructMatrixVectorView__object* self)
{
  sidl_rmi_InstanceHandle conn = (sidl_rmi_InstanceHandle)self->d_data;
  sidl_BaseInterface _ex = NULL;
  if(conn != NULL) {
    return sidl_rmi_InstanceHandle_getURL(conn, &_ex);
  }
  return NULL;
}

/* REMOTE EXEC: call the exec function for the object. */
static void remote_bHYPRE__SStructMatrixVectorView__exec(
  struct bHYPRE__SStructMatrixVectorView__object* self,
  const char* methodName,
  sidl_io_Deserializer inArgs,
  sidl_io_Serializer outArgs)
{
}

/* REMOTE METHOD STUB:addRef */
static void
remote_bHYPRE__SStructMatrixVectorView_addRef(
  /* in */ struct bHYPRE__SStructMatrixVectorView__object* self /* TLD */)
{
  /* FIXME  need to think through all of these special cases */
}

/* REMOTE METHOD STUB:deleteRef */
static void
remote_bHYPRE__SStructMatrixVectorView_deleteRef(
  /* in */ struct bHYPRE__SStructMatrixVectorView__object* self /* TLD */)
{
  sidl_BaseInterface _ex = NULL;
  sidl_BaseInterface *_ex2 =&_ex;
  /* initialize a new invocation */
  sidl_rmi_InstanceHandle _conn = (sidl_rmi_InstanceHandle)self->d_data;
  sidl_rmi_Invocation _inv = sidl_rmi_InstanceHandle_createInvocation( _conn,
    "deleteRef", _ex2 );
  sidl_rmi_Response _rsvp = NULL;

  /* pack in and inout arguments */

  /* send actual RMI request */
  _rsvp = sidl_rmi_Invocation_invokeMethod(_inv,_ex2);

  /* extract return value */

  /* unpack out and inout arguments */

  /* cleanup and return */
  sidl_rmi_Response_done(_rsvp, _ex2);
  sidl_rmi_Invocation_deleteRef(_inv);
  sidl_rmi_Response_deleteRef(_rsvp);
}

/* REMOTE METHOD STUB:isSame */
static sidl_bool
remote_bHYPRE__SStructMatrixVectorView_isSame(
  /* in */ struct bHYPRE__SStructMatrixVectorView__object* self /* TLD */,
  /* in */ struct sidl_BaseInterface__object* iobj)
{
  /* FIXME  need to think through all of these special cases */
  return 0;
}

/* REMOTE METHOD STUB:queryInt */
static struct sidl_BaseInterface__object*
remote_bHYPRE__SStructMatrixVectorView_queryInt(
  /* in */ struct bHYPRE__SStructMatrixVectorView__object* self /* TLD */,
  /* in */ const char* name)
{
  /* FIXME  need to think through all of these special cases */
  return 0;
}

/* REMOTE METHOD STUB:isType */
static sidl_bool
remote_bHYPRE__SStructMatrixVectorView_isType(
  /* in */ struct bHYPRE__SStructMatrixVectorView__object* self /* TLD */,
  /* in */ const char* name)
{
  sidl_BaseInterface _ex = NULL;
  sidl_BaseInterface *_ex2 =&_ex;
  /* initialize a new invocation */
  sidl_rmi_InstanceHandle _conn = (sidl_rmi_InstanceHandle)self->d_data;
  sidl_rmi_Invocation _inv = sidl_rmi_InstanceHandle_createInvocation( _conn,
    "isType", _ex2 );
  sidl_rmi_Response _rsvp = NULL;
  sidl_bool _retval;

  /* pack in and inout arguments */
  sidl_rmi_Invocation_packString( _inv, "name", name, _ex2);

  /* send actual RMI request */
  _rsvp = sidl_rmi_Invocation_invokeMethod(_inv,_ex2);

  /* extract return value */
  sidl_rmi_Response_unpackBool( _rsvp, "_retval", &_retval, _ex2);

  /* unpack out and inout arguments */

  /* cleanup and return */
  sidl_rmi_Response_done(_rsvp, _ex2);
  sidl_rmi_Invocation_deleteRef(_inv);
  sidl_rmi_Response_deleteRef(_rsvp);
  return _retval;
}

/* REMOTE METHOD STUB:getClassInfo */
static struct sidl_ClassInfo__object*
remote_bHYPRE__SStructMatrixVectorView_getClassInfo(
  /* in */ struct bHYPRE__SStructMatrixVectorView__object* self /* TLD */)
{
  /* FIXME  need to think through all of these special cases */
  return 0;
}

/* REMOTE METHOD STUB:SetCommunicator */
static int32_t
remote_bHYPRE__SStructMatrixVectorView_SetCommunicator(
  /* in */ struct bHYPRE__SStructMatrixVectorView__object* self /* TLD */,
  /* in */ struct bHYPRE_MPICommunicator__object* mpi_comm)
{
  sidl_BaseInterface _ex = NULL;
  sidl_BaseInterface *_ex2 =&_ex;
  /* initialize a new invocation */
  sidl_rmi_InstanceHandle _conn = (sidl_rmi_InstanceHandle)self->d_data;
  sidl_rmi_Invocation _inv = sidl_rmi_InstanceHandle_createInvocation( _conn,
    "SetCommunicator", _ex2 );
  sidl_rmi_Response _rsvp = NULL;
  int32_t _retval;

  /* pack in and inout arguments */
  sidl_rmi_Invocation_packString( _inv, "mpi_comm",
    bHYPRE_MPICommunicator__getURL(mpi_comm), _ex2);

  /* send actual RMI request */
  _rsvp = sidl_rmi_Invocation_invokeMethod(_inv,_ex2);

  /* extract return value */
  sidl_rmi_Response_unpackInt( _rsvp, "_retval", &_retval, _ex2);

  /* unpack out and inout arguments */

  /* cleanup and return */
  sidl_rmi_Response_done(_rsvp, _ex2);
  sidl_rmi_Invocation_deleteRef(_inv);
  sidl_rmi_Response_deleteRef(_rsvp);
  return _retval;
}

/* REMOTE METHOD STUB:Initialize */
static int32_t
remote_bHYPRE__SStructMatrixVectorView_Initialize(
  /* in */ struct bHYPRE__SStructMatrixVectorView__object* self /* TLD */)
{
  sidl_BaseInterface _ex = NULL;
  sidl_BaseInterface *_ex2 =&_ex;
  /* initialize a new invocation */
  sidl_rmi_InstanceHandle _conn = (sidl_rmi_InstanceHandle)self->d_data;
  sidl_rmi_Invocation _inv = sidl_rmi_InstanceHandle_createInvocation( _conn,
    "Initialize", _ex2 );
  sidl_rmi_Response _rsvp = NULL;
  int32_t _retval;

  /* pack in and inout arguments */

  /* send actual RMI request */
  _rsvp = sidl_rmi_Invocation_invokeMethod(_inv,_ex2);

  /* extract return value */
  sidl_rmi_Response_unpackInt( _rsvp, "_retval", &_retval, _ex2);

  /* unpack out and inout arguments */

  /* cleanup and return */
  sidl_rmi_Response_done(_rsvp, _ex2);
  sidl_rmi_Invocation_deleteRef(_inv);
  sidl_rmi_Response_deleteRef(_rsvp);
  return _retval;
}

/* REMOTE METHOD STUB:Assemble */
static int32_t
remote_bHYPRE__SStructMatrixVectorView_Assemble(
  /* in */ struct bHYPRE__SStructMatrixVectorView__object* self /* TLD */)
{
  sidl_BaseInterface _ex = NULL;
  sidl_BaseInterface *_ex2 =&_ex;
  /* initialize a new invocation */
  sidl_rmi_InstanceHandle _conn = (sidl_rmi_InstanceHandle)self->d_data;
  sidl_rmi_Invocation _inv = sidl_rmi_InstanceHandle_createInvocation( _conn,
    "Assemble", _ex2 );
  sidl_rmi_Response _rsvp = NULL;
  int32_t _retval;

  /* pack in and inout arguments */

  /* send actual RMI request */
  _rsvp = sidl_rmi_Invocation_invokeMethod(_inv,_ex2);

  /* extract return value */
  sidl_rmi_Response_unpackInt( _rsvp, "_retval", &_retval, _ex2);

  /* unpack out and inout arguments */

  /* cleanup and return */
  sidl_rmi_Response_done(_rsvp, _ex2);
  sidl_rmi_Invocation_deleteRef(_inv);
  sidl_rmi_Response_deleteRef(_rsvp);
  return _retval;
}

/* REMOTE METHOD STUB:GetObject */
static int32_t
remote_bHYPRE__SStructMatrixVectorView_GetObject(
  /* in */ struct bHYPRE__SStructMatrixVectorView__object* self /* TLD */,
  /* out */ struct sidl_BaseInterface__object** A)
{
  sidl_BaseInterface _ex = NULL;
  sidl_BaseInterface *_ex2 =&_ex;
  /* initialize a new invocation */
  sidl_rmi_InstanceHandle _conn = (sidl_rmi_InstanceHandle)self->d_data;
  sidl_rmi_Invocation _inv = sidl_rmi_InstanceHandle_createInvocation( _conn,
    "GetObject", _ex2 );
  sidl_rmi_Response _rsvp = NULL;
  char* A_str= NULL;
  int32_t _retval;

  /* pack in and inout arguments */

  /* send actual RMI request */
  _rsvp = sidl_rmi_Invocation_invokeMethod(_inv,_ex2);

  /* extract return value */
  sidl_rmi_Response_unpackInt( _rsvp, "_retval", &_retval, _ex2);

  /* unpack out and inout arguments */
  sidl_rmi_Response_unpackString( _rsvp, "A", &A_str, _ex2);
  sidl_BaseInterface__connect(A_str, _ex2);

  /* cleanup and return */
  sidl_rmi_Response_done(_rsvp, _ex2);
  sidl_rmi_Invocation_deleteRef(_inv);
  sidl_rmi_Response_deleteRef(_rsvp);
  return _retval;
}

/* REMOTE EPV: create remote entry point vectors (EPVs). */
static void bHYPRE__SStructMatrixVectorView__init_remote_epv(void)
{
  /* assert( HAVE_LOCKED_STATIC_GLOBALS ); */
  struct bHYPRE__SStructMatrixVectorView__epv* epv = 
    &s_rem_epv__bhypre__sstructmatrixvectorview;
  struct bHYPRE_MatrixVectorView__epv*         e0  = 
    &s_rem_epv__bhypre_matrixvectorview;
  struct bHYPRE_ProblemDefinition__epv*        e1  = 
    &s_rem_epv__bhypre_problemdefinition;
  struct bHYPRE_SStructMatrixVectorView__epv*  e2  = 
    &s_rem_epv__bhypre_sstructmatrixvectorview;
  struct sidl_BaseInterface__epv*              e3  = 
    &s_rem_epv__sidl_baseinterface;

  epv->f__cast                = remote_bHYPRE__SStructMatrixVectorView__cast;
  epv->f__delete              = remote_bHYPRE__SStructMatrixVectorView__delete;
  epv->f__exec                = remote_bHYPRE__SStructMatrixVectorView__exec;
  epv->f__getURL              = remote_bHYPRE__SStructMatrixVectorView__getURL;
  epv->f__ctor                = NULL;
  epv->f__dtor                = NULL;
  epv->f_addRef               = remote_bHYPRE__SStructMatrixVectorView_addRef;
  epv->f_deleteRef            = 
    remote_bHYPRE__SStructMatrixVectorView_deleteRef;
  epv->f_isSame               = remote_bHYPRE__SStructMatrixVectorView_isSame;
  epv->f_queryInt             = remote_bHYPRE__SStructMatrixVectorView_queryInt;
  epv->f_isType               = remote_bHYPRE__SStructMatrixVectorView_isType;
  epv->f_getClassInfo         = 
    remote_bHYPRE__SStructMatrixVectorView_getClassInfo;
  epv->f_SetCommunicator      = 
    remote_bHYPRE__SStructMatrixVectorView_SetCommunicator;
  epv->f_Initialize           = 
    remote_bHYPRE__SStructMatrixVectorView_Initialize;
  epv->f_Assemble             = remote_bHYPRE__SStructMatrixVectorView_Assemble;
  epv->f_GetObject            = 
    remote_bHYPRE__SStructMatrixVectorView_GetObject;

  e0->f__cast           = (void* (*)(void*,const char*)) epv->f__cast;
  e0->f__delete         = (void (*)(void*)) epv->f__delete;
  e0->f__exec           = (void (*)(void*,const char*,
    struct sidl_io_Deserializer__object*,
    struct sidl_io_Serializer__object*)) epv->f__exec;
  e0->f_addRef          = (void (*)(void*)) epv->f_addRef;
  e0->f_deleteRef       = (void (*)(void*)) epv->f_deleteRef;
  e0->f_isSame          = (sidl_bool (*)(void*,
    struct sidl_BaseInterface__object*)) epv->f_isSame;
  e0->f_queryInt        = (struct sidl_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInt;
  e0->f_isType          = (sidl_bool (*)(void*,const char*)) epv->f_isType;
  e0->f_getClassInfo    = (struct sidl_ClassInfo__object* (*)(void*)) 
    epv->f_getClassInfo;
  e0->f_SetCommunicator = (int32_t (*)(void*,
    struct bHYPRE_MPICommunicator__object*)) epv->f_SetCommunicator;
  e0->f_Initialize      = (int32_t (*)(void*)) epv->f_Initialize;
  e0->f_Assemble        = (int32_t (*)(void*)) epv->f_Assemble;

  e1->f__cast           = (void* (*)(void*,const char*)) epv->f__cast;
  e1->f__delete         = (void (*)(void*)) epv->f__delete;
  e1->f__exec           = (void (*)(void*,const char*,
    struct sidl_io_Deserializer__object*,
    struct sidl_io_Serializer__object*)) epv->f__exec;
  e1->f_addRef          = (void (*)(void*)) epv->f_addRef;
  e1->f_deleteRef       = (void (*)(void*)) epv->f_deleteRef;
  e1->f_isSame          = (sidl_bool (*)(void*,
    struct sidl_BaseInterface__object*)) epv->f_isSame;
  e1->f_queryInt        = (struct sidl_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInt;
  e1->f_isType          = (sidl_bool (*)(void*,const char*)) epv->f_isType;
  e1->f_getClassInfo    = (struct sidl_ClassInfo__object* (*)(void*)) 
    epv->f_getClassInfo;
  e1->f_SetCommunicator = (int32_t (*)(void*,
    struct bHYPRE_MPICommunicator__object*)) epv->f_SetCommunicator;
  e1->f_Initialize      = (int32_t (*)(void*)) epv->f_Initialize;
  e1->f_Assemble        = (int32_t (*)(void*)) epv->f_Assemble;

  e2->f__cast           = (void* (*)(void*,const char*)) epv->f__cast;
  e2->f__delete         = (void (*)(void*)) epv->f__delete;
  e2->f__exec           = (void (*)(void*,const char*,
    struct sidl_io_Deserializer__object*,
    struct sidl_io_Serializer__object*)) epv->f__exec;
  e2->f_addRef          = (void (*)(void*)) epv->f_addRef;
  e2->f_deleteRef       = (void (*)(void*)) epv->f_deleteRef;
  e2->f_isSame          = (sidl_bool (*)(void*,
    struct sidl_BaseInterface__object*)) epv->f_isSame;
  e2->f_queryInt        = (struct sidl_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInt;
  e2->f_isType          = (sidl_bool (*)(void*,const char*)) epv->f_isType;
  e2->f_getClassInfo    = (struct sidl_ClassInfo__object* (*)(void*)) 
    epv->f_getClassInfo;
  e2->f_SetCommunicator = (int32_t (*)(void*,
    struct bHYPRE_MPICommunicator__object*)) epv->f_SetCommunicator;
  e2->f_Initialize      = (int32_t (*)(void*)) epv->f_Initialize;
  e2->f_Assemble        = (int32_t (*)(void*)) epv->f_Assemble;
  e2->f_GetObject       = (int32_t (*)(void*,
    struct sidl_BaseInterface__object**)) epv->f_GetObject;

  e3->f__cast        = (void* (*)(void*,const char*)) epv->f__cast;
  e3->f__delete      = (void (*)(void*)) epv->f__delete;
  e3->f__exec        = (void (*)(void*,const char*,
    struct sidl_io_Deserializer__object*,
    struct sidl_io_Serializer__object*)) epv->f__exec;
  e3->f_addRef       = (void (*)(void*)) epv->f_addRef;
  e3->f_deleteRef    = (void (*)(void*)) epv->f_deleteRef;
  e3->f_isSame       = (sidl_bool (*)(void*,
    struct sidl_BaseInterface__object*)) epv->f_isSame;
  e3->f_queryInt     = (struct sidl_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInt;
  e3->f_isType       = (sidl_bool (*)(void*,const char*)) epv->f_isType;
  e3->f_getClassInfo = (struct sidl_ClassInfo__object* (*)(void*)) 
    epv->f_getClassInfo;

  s_remote_initialized = 1;
}

/* Create an instance that connects to an existing remote object. */
static struct bHYPRE_SStructMatrixVectorView__object*
bHYPRE_SStructMatrixVectorView__remoteConnect(const char *url,
  sidl_BaseInterface *_ex)
{
  struct bHYPRE__SStructMatrixVectorView__object* self;

  struct bHYPRE__SStructMatrixVectorView__object* s0;

  sidl_rmi_InstanceHandle instance = 
    sidl_rmi_ProtocolFactory_connectInstance(url, _ex );
  if ( instance == NULL) { return NULL; }
  self =
    (struct bHYPRE__SStructMatrixVectorView__object*) malloc(
      sizeof(struct bHYPRE__SStructMatrixVectorView__object));

   s0 =                                          self;

  LOCK_STATIC_GLOBALS;
  if (!s_remote_initialized) {
    bHYPRE__SStructMatrixVectorView__init_remote_epv();
  }
  UNLOCK_STATIC_GLOBALS;

  s0->d_bhypre_matrixvectorview.d_epv    = &s_rem_epv__bhypre_matrixvectorview;
  s0->d_bhypre_matrixvectorview.d_object = (void*) self;

  s0->d_bhypre_problemdefinition.d_epv    = 
    &s_rem_epv__bhypre_problemdefinition;
  s0->d_bhypre_problemdefinition.d_object = (void*) self;

  s0->d_bhypre_sstructmatrixvectorview.d_epv    = 
    &s_rem_epv__bhypre_sstructmatrixvectorview;
  s0->d_bhypre_sstructmatrixvectorview.d_object = (void*) self;

  s0->d_sidl_baseinterface.d_epv    = &s_rem_epv__sidl_baseinterface;
  s0->d_sidl_baseinterface.d_object = (void*) self;

  s0->d_data = (void*) instance;
  s0->d_epv  = &s_rem_epv__bhypre__sstructmatrixvectorview;

  self->d_data = (void*) instance;

  return bHYPRE_SStructMatrixVectorView__cast(self);
}
/* Create an instance that uses an already existing InstanceHandel to connect 
  to an existing remote object. */
static struct bHYPRE_SStructMatrixVectorView__object*
bHYPRE_SStructMatrixVectorView__IHConnect(sidl_rmi_InstanceHandle instance,
  sidl_BaseInterface *_ex)
{
  struct bHYPRE__SStructMatrixVectorView__object* self;

  struct bHYPRE__SStructMatrixVectorView__object* s0;

  self =
    (struct bHYPRE__SStructMatrixVectorView__object*) malloc(
      sizeof(struct bHYPRE__SStructMatrixVectorView__object));

   s0 =                                          self;

  LOCK_STATIC_GLOBALS;
  if (!s_remote_initialized) {
    bHYPRE__SStructMatrixVectorView__init_remote_epv();
  }
  UNLOCK_STATIC_GLOBALS;

  s0->d_bhypre_matrixvectorview.d_epv    = &s_rem_epv__bhypre_matrixvectorview;
  s0->d_bhypre_matrixvectorview.d_object = (void*) self;

  s0->d_bhypre_problemdefinition.d_epv    = 
    &s_rem_epv__bhypre_problemdefinition;
  s0->d_bhypre_problemdefinition.d_object = (void*) self;

  s0->d_bhypre_sstructmatrixvectorview.d_epv    = 
    &s_rem_epv__bhypre_sstructmatrixvectorview;
  s0->d_bhypre_sstructmatrixvectorview.d_object = (void*) self;

  s0->d_sidl_baseinterface.d_epv    = &s_rem_epv__sidl_baseinterface;
  s0->d_sidl_baseinterface.d_object = (void*) self;

  s0->d_data = (void*) instance;
  s0->d_epv  = &s_rem_epv__bhypre__sstructmatrixvectorview;

  self->d_data = (void*) instance;

  sidl_rmi_InstanceHandle_addRef(instance);
  return bHYPRE_SStructMatrixVectorView__cast(self);
}