/* Orx - Portable Game Engine
 *
 * Copyright (c) 2008-2018 Orx-Project
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */

/**
 * @file orxObject.h
 * @date 01/12/2003
 * @author iarwain@orx-project.org
 *
 * @todo
 */

/**
 * @addtogroup orxObject
 *
 * Object module
 * Allows to creates and handle objects
 * Objects are structures containers that can refer to many other structures such as frames, graphics, etc...
 *
 * @{
 */


#ifndef _orxOBJECT_H_
#define _orxOBJECT_H_


#include "orxInclude.h"

#include "anim/orxAnimSet.h"
#include "core/orxClock.h"
#include "display/orxDisplay.h"
#include "display/orxGraphic.h"
#include "display/orxTexture.h"
#include "math/orxOBox.h"
#include "memory/orxBank.h"
#include "object/orxStructure.h"
#include "sound/orxSound.h"


/** Defines */
#define orxOBJECT_GET_STRUCTURE(OBJECT, TYPE) orx##TYPE(_orxObject_GetStructure(OBJECT, orxSTRUCTURE_ID_##TYPE))

#define orxOBJECT_KZ_DEFAULT_GROUP          "default"


/** Event enum
 */
typedef enum __orxOBJECT_EVENT_t
{
  orxOBJECT_EVENT_CREATE = 0,
  orxOBJECT_EVENT_DELETE,
  orxOBJECT_EVENT_PREPARE,
  orxOBJECT_EVENT_ENABLE,
  orxOBJECT_EVENT_DISABLE,
  orxOBJECT_EVENT_PAUSE,
  orxOBJECT_EVENT_UNPAUSE,

  orxOBJECT_EVENT_NUMBER,

  orxOBJECT_EVENT_NONE = orxENUM_NONE

} orxOBJECT_EVENT;


/** Internal object structure */
typedef struct __orxOBJECT_t                orxOBJECT;


/** @name Internal module function
 * @{ */
/** Object module setup
 */
extern orxDLLAPI void orxFASTCALL           orxObject_Setup();

/** Inits the object module.
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_Init();

/** Exits from the object module.
 */
extern orxDLLAPI void orxFASTCALL           orxObject_Exit();
/** @} */

/** @name Basic handling
 * @{ */
/** Creates an empty object.
 * @return orxOBJECT / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_Create();

/** Creates an object from config.
 * @param[in]   _zConfigID    Config ID
 * @ return orxOBJECT / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_CreateFromConfig(const orxSTRING _zConfigID);

/** Deletes an object, *unsafe* when called from an event handler: call orxObject_SetLifeTime(orxFLOAT_0) instead
 * @param[in] _pstObject        Concerned object
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_Delete(orxOBJECT *_pstObject);

/** Updates an object.
 * @param[in] _pstObject        Concerned object
 * @param[in] _pstClockInfo     Clock information used to compute new object's state
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_Update(orxOBJECT *_pstObject, const orxCLOCK_INFO *_pstClockInfo);

/** Enables/disables an object. Note that enabling/disabling an object is not recursive, so its children will not be affected, see orxObject_EnableRecursive().
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _bEnable      Enable / disable
 */
extern orxDLLAPI void orxFASTCALL           orxObject_Enable(orxOBJECT *_pstObject, orxBOOL _bEnable);

/** Enables/disables an object and all its children.
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _bEnable      Enable / disable
 */
extern orxDLLAPI void orxFASTCALL           orxObject_EnableRecursive(orxOBJECT *_pstObject, orxBOOL _bEnable);

/** Is object enabled?
 * @param[in]   _pstObject    Concerned object
 * @return      orxTRUE if enabled, orxFALSE otherwise
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_IsEnabled(const orxOBJECT *_pstObject);

/** Pauses/unpauses an object. Note that pausing an object is not recursive, so its children will not be affected, see orxObject_PauseRecursive().
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _bPause       Pause / unpause
 */
extern orxDLLAPI void orxFASTCALL           orxObject_Pause(orxOBJECT *_pstObject, orxBOOL _bPause);

/** Pauses/unpauses an object and its children.
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _bPause       Pause / unpause
 */
extern orxDLLAPI void orxFASTCALL           orxObject_PauseRecursive(orxOBJECT *_pstObject, orxBOOL _bPause);

/** Is object paused?
 * @param[in]   _pstObject    Concerned object
 * @return      orxTRUE if paused, orxFALSE otherwise
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_IsPaused(const orxOBJECT *_pstObject);
/** @} */


/** @name User data
 * @{ */
/** Sets user data for an object. Orx ignores the user data, this is a mechanism for attaching custom
 * data to be used later by user code.
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _pUserData    User data to store / orxNULL
 */
extern orxDLLAPI void orxFASTCALL           orxObject_SetUserData(orxOBJECT *_pstObject, void *_pUserData);

/** Gets object's user data.
 * @param[in]   _pstObject    Concerned object
 * @return      Stored user data / orxNULL
 */
extern orxDLLAPI void *orxFASTCALL          orxObject_GetUserData(const orxOBJECT *_pstObject);
/** @} */

/** @name Ownership
 * @{ */
/** Sets owner for an object. Ownership in Orx is only about lifetime management. That is, when an object
 * dies, it also kills its children. Compare this with orxObject_SetParent().
 *
 * Note that the "ChildList" field of an object's config section implies two things; that the object is both
 * the owner (orxObject_SetOwner()) and the parent (orxObject_SetParent()) of its children. There is an
 * exception to this though; when an object's child has a parent camera, the object is only the owner, and
 * the camera is the parent.
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _pOwner       Owner to set / orxNULL, if owner is an orxOBJECT, the owned object will be added to it as a children
 */
extern orxDLLAPI void orxFASTCALL           orxObject_SetOwner(orxOBJECT *_pstObject, void *_pOwner);

/** Gets object's owner. See orxObject_SetOwner().
 * @param[in]   _pstObject    Concerned object
 * @return      Owner / orxNULL
 */
extern orxDLLAPI orxSTRUCTURE *orxFASTCALL  orxObject_GetOwner(const orxOBJECT *_pstObject);

/** Gets object's first owned child (only if created with a config ChildList / has an owner set with orxObject_SetOwner)
 * see orxObject_SetOwner() and orxObject_SetParent() for a comparison of ownership and parenthood in Orx.
 *
 * This function is typically used to iterate over the owned children of an object. For example;
 * @code
 * for(orxOBJECT * pstChild = orxObject_GetOwnedChild(pstObject);
 *     pstChild;
 *     pstChild = orxObject_GetOwnedSibling(pstChild))
 * {
 *     do_something(pstChild);
 * } @endcode
 * @param[in]   _pstObject    Concerned object
 * @return      First owned child object / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_GetOwnedChild(const orxOBJECT *_pstObject);

/** Gets object's next owned sibling (only if created with a config ChildList / has an owner set with orxObject_SetOwner)
 * This function is typically used to iterate over the owned children of an object, see orxObject_GetOwnedChild() for an example.
 * @param[in]   _pstObject    Concerned object
 * @return      Next sibling object / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_GetOwnedSibling(const orxOBJECT *_pstObject);
/** @} */


/** @name Clock
 * @{ */
/** Sets associated clock for an object.
 * @param[in]   _pstObject    Concerned object
 * @param[in]   _pstClock     Clock to associate / orxNULL
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetClock(orxOBJECT *_pstObject, orxCLOCK *_pstClock);

/** Gets object's clock.
 * @param[in]   _pstObject    Concerned object
 * @return      Associated clock / orxNULL
 */
extern orxDLLAPI orxCLOCK *orxFASTCALL      orxObject_GetClock(const orxOBJECT *_pstObject);
/** @} */


/** @name Linked structures
 * @{ */
/** Links a structure to an object.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pstStructure   Structure to link
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_LinkStructure(orxOBJECT *_pstObject, orxSTRUCTURE *_pstStructure);

/** Unlinks structure from an object, given its structure ID.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _eStructureID   ID of structure to unlink
 */
extern orxDLLAPI void orxFASTCALL           orxObject_UnlinkStructure(orxOBJECT *_pstObject, orxSTRUCTURE_ID _eStructureID);


/** Structure used by an object get accessor, given its structure ID. Structure must then be cast correctly. (see helper macro
 * #orxOBJECT_GET_STRUCTURE())
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _eStructureID   ID of the structure to get
 * @return orxSTRUCTURE / orxNULL
 */
extern orxDLLAPI orxSTRUCTURE *orxFASTCALL  _orxObject_GetStructure(const orxOBJECT *_pstObject, orxSTRUCTURE_ID _eStructureID);
/** @} */


/** @name Flip
 * @{ */
/** Sets object flipping.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _bFlipX         Flip it on X axis
 * @param[in]   _bFlipY         Flip it on Y axis
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetFlip(orxOBJECT *_pstObject, orxBOOL _bFlipX, orxBOOL _bFlipY);

/** Gets object flipping.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pbFlipX        X axis flipping
 * @param[in]   _pbFlipY        Y axis flipping
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_GetFlip(const orxOBJECT *_pstObject, orxBOOL *_pbFlipX, orxBOOL *_pbFlipY);
/** @} */


/** @name Graphic
 * @{ */
/** Sets object pivot. This is a convenience wrapper around orxGraphic_SetPivot(). The "pivot" is essentially
 * what is indicated by the "Pivot" field of a config graphic section.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvPivot        Object pivot
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetPivot(orxOBJECT *_pstObject, const orxVECTOR *_pvPivot);

/** Sets object origin. This is a convenience wrapper around orxGraphic_SetOrigin(). The "origin" of a graphic is
 * essentially what is indicated by the "TextureOrigin" field of a config graphic section. The "origin" together with
 * "size" (see orxObject_SetSize()) defines the sprite of an object.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvOrigin       Object origin
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetOrigin(orxOBJECT *_pstObject, const orxVECTOR *_pvOrigin);

/** Sets object size. For objects that have a graphic attached it's simply a convenience wrapper for orxGraphic_SetSize(),
 * but an object can also have a size without a graphic.
 *
 * Note the difference between "Scale" and "Size". The size of an object with a non-text graphic is the sprite size in
 * pixels on its texture. The object's effective size for rendering and intersection purposes (see orxObject_Pick()
 * and friends) is proportional to its "size" multiplied by its "scale". Another important distinction is that the
 * scale of an object also affects its children (see orxObject_SetParent() and note the distinction between
 * parenthood and ownership).
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvSize       	Object size
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetSize(orxOBJECT *_pstObject, const orxVECTOR *_pvSize);

/** Get object pivot. See orxObject_SetPivot() for a more detailed explanation.
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvPivot        Object pivot
 * @return      orxVECTOR / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetPivot(const orxOBJECT *_pstObject, orxVECTOR *_pvPivot);

/** Get object origin. See orxObject_SetOrigin() for a more detailed explanation.
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvOrigin       Object origin
 * @return      orxVECTOR / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetOrigin(const orxOBJECT *_pstObject, orxVECTOR *_pvOrigin);

/** Gets object size. See orxObject_SetSize() for a more detailed explanation.
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvSize         Object's size
 * @return      orxVECTOR / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetSize(const orxOBJECT *_pstObject, orxVECTOR *_pvSize);
/** @} */


/** @name Frame
 * @{ */
/** Sets object position in its parent's reference frame. See orxObject_SetWorldPosition() for setting an object's
 * position in the global reference frame.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvPosition     Object position
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetPosition(orxOBJECT *_pstObject, const orxVECTOR *_pvPosition);

/** Sets object position in the global reference frame. See orxObject_SetPosition() for setting an object's position
 * in its parent's reference frame.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvPosition     Object world position
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetWorldPosition(orxOBJECT *_pstObject, const orxVECTOR *_pvPosition);

/** Sets object rotation in its parent's reference frame. See orxObject_SetWorldRotation() for setting an object's
 * rotation in the global reference frame.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fRotation      Object rotation (radians)
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetRotation(orxOBJECT *_pstObject, orxFLOAT _fRotation);

/** Sets object rotation in the global reference frame. See orxObject_SetRotation() for setting an object's rotation
 * in its parent's reference frame.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fRotation      Object world rotation (radians)
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetWorldRotation(orxOBJECT *_pstObject, orxFLOAT _fRotation);

/** Sets object scale in its parent's reference frame. See orxObject_SetWorldScale() for setting an object's scale
 * in the global reference frame.
 * See orxObject_SetSize() for a deeper explanation of the "size" of an object.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvScale        Object scale vector
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetScale(orxOBJECT *_pstObject, const orxVECTOR *_pvScale);

/** Sets object scale in the global reference frame. See orxObject_SetScale() for setting an object's scale in its
 * parent's reference frame.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvScale        Object world scale vector
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetWorldScale(orxOBJECT *_pstObject, const orxVECTOR *_pvScale);

/** Get object position. See orxObject_SetPosition().
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvPosition     Object position
 * @return      orxVECTOR / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetPosition(const orxOBJECT *_pstObject, orxVECTOR *_pvPosition);

/** Get object world position. See orxObject_SetWorldPosition().
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvPosition     Object world position
 * @return      orxVECTOR / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetWorldPosition(const orxOBJECT *_pstObject, orxVECTOR *_pvPosition);

/** Get object rotation. See orxObject_SetRotation().
 * @param[in]   _pstObject      Concerned object
 * @return      orxFLOAT (radians)
 */
extern orxDLLAPI orxFLOAT orxFASTCALL       orxObject_GetRotation(const orxOBJECT *_pstObject);

/** Get object world rotation. See orxObject_SetWorldRotation().
 * @param[in]   _pstObject      Concerned object
 * @return      orxFLOAT (radians)
 */
extern orxDLLAPI orxFLOAT orxFASTCALL       orxObject_GetWorldRotation(const orxOBJECT *_pstObject);

/** Get object scale. See orxObject_SetScale().
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvScale        Object scale vector
 * @return      Scale vector
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetScale(const orxOBJECT *_pstObject, orxVECTOR *_pvScale);

/** Gets object world scale. See orxObject_SetWorldScale().
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvScale        Object world scale
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetWorldScale(const orxOBJECT *_pstObject, orxVECTOR *_pvScale);
/** @} */


/** @name Parent
 * @{ */
/** Sets an object parent (in the frame hierarchy). Parenthood in orx is about the transformation (position,
 * rotation, scale) of objects. Transformation of objects are compounded in a frame hierarchy. Compare this
 * with orxObject_SetOwner()
 *
 * Note that the "ChildList" field of an object's config section implies two things; that the object is both
 * the owner (orxObject_SetOwner()) and the parent (orxObject_SetParent()) of its children. There is an
 * exception to this though; when an object's child has a parent camera, the object is only the owner, and
 * the camera is the parent.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pParent        Parent structure to set (object, spawner, camera or frame) / orxNULL
 * @return      orsSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetParent(orxOBJECT *_pstObject, void *_pParent);

/** Gets object's parent. See orxObject_SetParent() for a more detailed explanation.
 * @param[in]   _pstObject    Concerned object
 * @return      Parent (object, spawner, camera or frame) / orxNULL
 */
extern orxDLLAPI orxSTRUCTURE *orxFASTCALL  orxObject_GetParent(const orxOBJECT *_pstObject);

/** Gets object's first child. See orxObject_SetOwner() and orxObject_SetParent() for a comparison of
 * ownership and parenthood in Orx.
 *
 * This function is typically used to iterate over the children of an object. For example;
 * @code
 * for(orxOBJECT * pstChild = orxObject_GetChild(pstObject);
 *     pstChild;
 *     pstChild = orxObject_GetSibling(pstChild))
 * {
 *     do_something(pstChild);
 * } @endcode
 * @param[in]   _pstObject    Concerned object
 * @return      First child structure (object, spawner, camera or frame) / orxNULL
 */
extern orxDLLAPI orxSTRUCTURE *orxFASTCALL  orxObject_GetChild(const orxOBJECT *_pstObject);

/** Gets object's next sibling. This function is typically used for iterating over the children of an object,
 * see orxObject_GetChild() for an iteration example.
 * @param[in]   _pstObject    Concerned object
 * @return      Next sibling structure (object, spawner, camera or frame) / orxNULL
 */
extern orxDLLAPI orxSTRUCTURE *orxFASTCALL  orxObject_GetSibling(const orxOBJECT *_pstObject);


/** Attaches an object to a parent while maintaining the object's world position.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pParent        Parent structure to attach to (object, spawner, camera or frame)
 * @return      orsSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_Attach(orxOBJECT *_pstObject, void *_pParent);

/** Detaches an object from a parent while maintaining the object's world position.
 * @param[in]   _pstObject      Concerned object
 * @return      orsSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_Detach(orxOBJECT *_pstObject);
/** @} */


/** @name Animation
 * @{ */
/** Sets an object animset.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pstAnimSet     Animation set to set / orxNULL
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetAnimSet(orxOBJECT *_pstObject, orxANIMSET *_pstAnimSet);


/** Sets an object's relative animation frequency.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fFrequency     Frequency to set: < 1.0 for slower than initial, > 1.0 for faster than initial
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetAnimFrequency(orxOBJECT *_pstObject, orxFLOAT _fFrequency);

/** Sets current animation for object. This function switches the currently displayed animation of the object
 * immediately. Compare this with orxObject_SetTargetAnim().
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zAnimName      Animation name (config's one) to set / orxNULL
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetCurrentAnim(orxOBJECT *_pstObject, const orxSTRING _zAnimName);

/** Sets target animation for object. The animations are sequenced on an object according to the animation link graph
 * defined by its AnimationSet. The sequence follows the graph and tries to reach the target animation. Use
 * orxObject_SetCurrentAnim() to switch the animation without using the link graph.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zAnimName      Animation name (config's one) to set / orxNULL
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetTargetAnim(orxOBJECT *_pstObject, const orxSTRING _zAnimName);

/** Is current animation test.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zAnimName      Animation name (config's one) to test
 * @return      orxTRUE / orxFALSE
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_IsCurrentAnim(const orxOBJECT *_pstObject, const orxSTRING _zAnimName);

/** Is target animation test.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zAnimName      Animation name (config's one) to test
 * @return      orxTRUE / orxFALSE
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_IsTargetAnim(const orxOBJECT *_pstObject, const orxSTRING _zAnimName);
/** @} */


/** @name Physics / dynamics
 * @{ */
/** Sets an object speed.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvSpeed        Speed to set
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetSpeed(orxOBJECT *_pstObject, const orxVECTOR *_pvSpeed);

/** Sets an object speed relative to its rotation/scale.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvRelativeSpeed Relative speed to set
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetRelativeSpeed(orxOBJECT *_pstObject, const orxVECTOR *_pvRelativeSpeed);

/** Sets an object angular velocity.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fVelocity      Angular velocity to set (radians/seconds)
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetAngularVelocity(orxOBJECT *_pstObject, orxFLOAT _fVelocity);

/** Sets an object custom gravity.
 * @param[in]   _pstObject        Concerned object
 * @param[in]   _pvCustomGravity  Custom gravity to set / orxNULL to remove it
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetCustomGravity(orxOBJECT *_pstObject, const orxVECTOR *_pvCustomGravity);

/** Gets an object speed.
 * @param[in]   _pstObject      Concerned object
 * @param[out]   _pvSpeed       Speed to get
 * @return      Object speed / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetSpeed(const orxOBJECT *_pstObject, orxVECTOR *_pvSpeed);

/** Gets an object relative speed.
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvRelativeSpeed Relative speed to get
 * @return      Object relative speed / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetRelativeSpeed(const orxOBJECT *_pstObject, orxVECTOR *_pvRelativeSpeed);

/** Gets an object angular velocity.
 * @param[in]   _pstObject      Concerned object
 * @return      Object angular velocity (radians/seconds)
 */
extern orxDLLAPI orxFLOAT orxFASTCALL       orxObject_GetAngularVelocity(const orxOBJECT *_pstObject);

/** Gets an object custom gravity.
 * @param[in]   _pstObject        Concerned object
 * @param[out]  _pvCustomGravity  Custom gravity to get
 * @return      Object custom gravity / orxNULL is object doesn't have any
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetCustomGravity(const orxOBJECT *_pstObject, orxVECTOR *_pvCustomGravity);

/** Gets an object mass.
 * @param[in]   _pstObject      Concerned object
 * @return      Object mass
 */
extern orxDLLAPI orxFLOAT orxFASTCALL       orxObject_GetMass(const orxOBJECT *_pstObject);

/** Gets an object center of mass (object space).
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pvMassCenter   Mass center to get
 * @return      Mass center / orxNULL
 */
extern orxDLLAPI orxVECTOR *orxFASTCALL     orxObject_GetMassCenter(const orxOBJECT *_pstObject, orxVECTOR *_pvMassCenter);


/** Applies a torque.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fTorque        Torque to apply
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_ApplyTorque(orxOBJECT *_pstObject, orxFLOAT _fTorque);

/** Applies a force.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvForce        Force to apply
 * @param[in]   _pvPoint        Point (world coordinates) where the force will be applied, if orxNULL, center of mass will be used
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_ApplyForce(orxOBJECT *_pstObject, const orxVECTOR *_pvForce, const orxVECTOR *_pvPoint);

/** Applies an impulse.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvImpulse      Impulse to apply
 * @param[in]   _pvPoint        Point (world coordinates) where the impulse will be applied, if orxNULL, center of mass will be used
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_ApplyImpulse(orxOBJECT *_pstObject, const orxVECTOR *_pvImpulse, const orxVECTOR *_pvPoint);


/** Issues a raycast to test for potential objects in the way.
 * @param[in]   _pvStart        Start of raycast
 * @param[in]   _pvEnd          End of raycast
 * @param[in]   _u16SelfFlags   Selfs flags used for filtering (0xFFFF for no filtering)
 * @param[in]   _u16CheckMask   Check mask used for filtering (0xFFFF for no filtering)
 * @param[in]   _bEarlyExit     Should stop as soon as an object has been hit (which might not be the closest)
 * @param[in]   _pvContact      If non-null and a contact is found it will be stored here
 * @param[in]   _pvNormal       If non-null and a contact is found, its normal will be stored here
 * @return Colliding orxOBJECT / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_Raycast(const orxVECTOR *_pvStart, const orxVECTOR *_pvEnd, orxU16 _u16SelfFlags, orxU16 _u16CheckMask, orxBOOL _bEarlyExit, orxVECTOR *_pvContact, orxVECTOR *_pvNormal);
/** @} */


/** @name Text
 * @{ */
/** Sets object text string, if object is associated to a text.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zString        String to set
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetTextString(orxOBJECT *_pstObject, const orxSTRING _zString);

/** Gets object text string, if object is associated to a text.
 * @param[in]   _pstObject      Concerned object
 * @return      orxSTRING / orxSTRING_EMPTY
 */
extern orxDLLAPI const orxSTRING orxFASTCALL orxObject_GetTextString(orxOBJECT *_pstObject);
/** @} */


/** @name Bounding box
 * @{ */
/** Gets object's bounding box (OBB).
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pstBoundingBox Bounding box result
 * @return      Bounding box / orxNULL
 */
extern orxDLLAPI orxOBOX *orxFASTCALL       orxObject_GetBoundingBox(const orxOBJECT *_pstObject, orxOBOX *_pstBoundingBox);
/** @} */


/** @name FX
 * @{ */
/** Adds an FX using its config ID.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zFXConfigID    Config ID of the FX to add
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddFX(orxOBJECT *_pstObject, const orxSTRING _zFXConfigID);

/** Adds a unique FX using its config ID. Refer to orxObject_AddUniqueDelayedFX() for details, since this
 * function is the same as it with the delay argument set to 0.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zFXConfigID    Config ID of the FX to add
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddUniqueFX(orxOBJECT *_pstObject, const orxSTRING _zFXConfigID);

/** Adds a delayed FX using its config ID.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zFXConfigID    Config ID of the FX to add
 * @param[in]   _fDelay         Delay time
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddDelayedFX(orxOBJECT *_pstObject, const orxSTRING _zFXConfigID, orxFLOAT _fDelay);

/** Adds a unique delayed FX using its config ID. The difference between this function and orxObject_AddDelayedFX()
 * is that this one does not add the specified FX, if the object already has an FX with the same config ID attached.
 * note that the "uniqueness" is determined immediately at the time of this function call, not at the time of the
 * FX start (i.e. after the delay).
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zFXConfigID    Config ID of the FX to add
 * @param[in]   _fDelay         Delay time
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddUniqueDelayedFX(orxOBJECT *_pstObject, const orxSTRING _zFXConfigID, orxFLOAT _fDelay);

/** Removes an FX using its config ID.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zFXConfigID    Config ID of the FX to remove
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_RemoveFX(orxOBJECT *_pstObject, const orxSTRING _zFXConfigID);

/** Synchronizes FXs with another object's ones (if FXs are not matching on both objects the behavior is undefined).
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pstModel       Model object on which to synchronize FXs
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SynchronizeFX(orxOBJECT *_pstObject, const orxOBJECT *_pstModel);
/** @} */


/** @name Sound
 * @{ */
/** Adds a sound using its config ID.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zSoundConfigID Config ID of the sound to add
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddSound(orxOBJECT *_pstObject, const orxSTRING _zSoundConfigID);

/** Removes a sound using its config ID.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zSoundConfigID Config ID of the sound to remove
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_RemoveSound(orxOBJECT *_pstObject, const orxSTRING _zSoundConfigID);

/** Gets last added sound (Do *NOT* destroy it directly before removing it!!!).
 * @param[in]   _pstObject      Concerned object
 * @return      orxSOUND / orxNULL
 */
extern orxDLLAPI orxSOUND *orxFASTCALL      orxObject_GetLastAddedSound(const orxOBJECT *_pstObject);

/** Sets volume for all sounds of an object.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fVolume        Desired volume (0.0 - 1.0)
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetVolume(orxOBJECT *_pstObject, orxFLOAT _fVolume);

/** Sets pitch for all sounds of an object.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fPitch         Desired pitch (0.0 - 1.0)
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetPitch(orxOBJECT *_pstObject, orxFLOAT _fPitch);

/** Plays all the sounds of an object.
 * @param[in]   _pstObject      Concerned object
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_Play(orxOBJECT *_pstObject);

/** Stops all the sounds of an object.
 * @param[in]   _pstObject      Concerned object
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_Stop(orxOBJECT *_pstObject);

/** @} */


/** @name Shader
 * @{ */
/** Adds a shader to an object using its config ID.
 * @param[in]   _pstObject        Concerned object
 * @param[in]   _zShaderConfigID  Config ID of the shader to add
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddShader(orxOBJECT *_pstObject, const orxSTRING _zShaderConfigID);

/** Removes a shader using its config ID.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zShaderConfigID Config ID of the shader to remove
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_RemoveShader(orxOBJECT *_pstObject, const orxSTRING _zShaderConfigID);

/** Enables an object's shader.
 * @param[in]   _pstObject        Concerned object
 * @param[in]   _bEnable          Enable / disable
 */
extern orxDLLAPI void orxFASTCALL           orxObject_EnableShader(orxOBJECT *_pstObject, orxBOOL _bEnable);

/** Is an object's shader enabled?
 * @param[in]   _pstObject        Concerned object
 * @return      orxTRUE if enabled, orxFALSE otherwise
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_IsShaderEnabled(const orxOBJECT *_pstObject);
/** @} */


/** @name TimeLine
 * @{ */
/** Adds a timeline track to an object using its config ID.
 * @param[in]   _pstObject        Concerned object
 * @param[in]   _zTrackConfigID   Config ID of the timeline track to add
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_AddTimeLineTrack(orxOBJECT *_pstObject, const orxSTRING _zTrackConfigID);

/** Removes a timeline track using its config ID
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _zTrackConfigID Config ID of the timeline track to remove
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_RemoveTimeLineTrack(orxOBJECT *_pstObject, const orxSTRING _zTrackConfigID);

/** Enables an object's timeline.
 * @param[in]   _pstObject        Concerned object
 * @param[in]   _bEnable          Enable / disable
 */
extern orxDLLAPI void orxFASTCALL           orxObject_EnableTimeLine(orxOBJECT *_pstObject, orxBOOL _bEnable);

/** Is an object's timeline enabled?
 * @param[in]   _pstObject        Concerned object
 * @return      orxTRUE if enabled, orxFALSE otherwise
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_IsTimeLineEnabled(const orxOBJECT *_pstObject);
/** @} */


/** @name Name
 * @{ */
/** Gets object config name.
 * @param[in]   _pstObject      Concerned object
 * @return      orxSTRING / orxSTRING_EMPTY
 */
extern orxDLLAPI const orxSTRING orxFASTCALL orxObject_GetName(const orxOBJECT *_pstObject);
/** @} */


/** @name Neighboring
 * @{ */
/** Creates a list of object at neighboring of the given box (ie. whose bounding volume intersects this box).
 * The following is an example for iterating over a neighbor list:
 * @code
 * orxVECTOR vPosition; // The world position of the neighborhood area
 * // set_position(vPosition);
 * orxVECTOR vSize; // The size of the neighborhood area
 * // set_size(vSize);
 * orxVECTOR vPivot; // The pivot of the neighborhood area
 * // set_pivot(vPivot);
 *
 * orxOBOX stBox;
 * orxOBox_2DSet(&stBox, &vPosition, &vPivot, &vSize, 0);
 *
 * orxBANK * pstBank = orxObject_CreateNeighborList(&stBox, orxU32_UNDEFINED);
 * if(pstBank) {
 *     for(int i=0; i < orxBank_GetCount(pstBank); ++i)
 *     {
 *         orxOBJECT * pstObject = *((orxOBJECT **) orxBank_GetAtIndex(pstBank, i));
 *         do_something_with(pstObject);
 *     }
 *     orxObject_DeleteNeighborList(pstBank);
 * }
 * @endcode
 * @param[in]   _pstCheckBox    Box to check intersection with
 * @param[in]   _u32GroupID     Group ID to consider, orxU32_UNDEFINED for all
 * @return      orxBANK / orxNULL
 */
extern orxDLLAPI orxBANK *orxFASTCALL       orxObject_CreateNeighborList(const orxOBOX *_pstCheckBox, orxU32 _u32GroupID);

/** Deletes an object list created with orxObject_CreateNeighborList().
 * @param[in]   _pstObjectList  Concerned object list
 */
extern orxDLLAPI void orxFASTCALL           orxObject_DeleteNeighborList(orxBANK *_pstObjectList);
/** @} */


/** @name Smoothing
 * @{ */
/** Sets object smoothing.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _eSmoothing     Smoothing type (enabled, default or none)
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetSmoothing(orxOBJECT *_pstObject, orxDISPLAY_SMOOTHING _eSmoothing);

/** Gets object smoothing.
 * @param[in]   _pstObject     Concerned object
 * @return Smoothing type (enabled, default or none)
 */
extern orxDLLAPI orxDISPLAY_SMOOTHING orxFASTCALL orxObject_GetSmoothing(const orxOBJECT *_pstObject);
/** @} */


/** @name texture
 * @{ */
/** Gets object working texture.
 * @param[in]   _pstObject     Concerned object
 * @return orxTEXTURE / orxNULL
 */
extern orxDLLAPI orxTEXTURE *orxFASTCALL    orxObject_GetWorkingTexture(const orxOBJECT *_pstObject);
/** @} */


/** @name graphic
 * @{ */
/** Gets object working graphic.
 * @param[in]   _pstObject     Concerned object
 * @return orxGRAPHIC / orxNULL
 */
extern orxDLLAPI orxGRAPHIC *orxFASTCALL    orxObject_GetWorkingGraphic(const orxOBJECT *_pstObject);

/** Sets object color.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pstColor       Color to set, orxNULL to remove any specific color
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetColor(orxOBJECT *_pstObject, const orxCOLOR *_pstColor);

/** Sets color of an object and all its children.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pstColor       Color to set, orxNULL to remove any specific color
 */
extern orxDLLAPI void orxFASTCALL           orxObject_SetColorRecursive(orxOBJECT *_pstObject, const orxCOLOR *_pstColor);

/** Object has color accessor?
 * @param[in]   _pstObject      Concerned object
 * @return      orxTRUE / orxFALSE
 */
extern orxDLLAPI orxBOOL orxFASTCALL        orxObject_HasColor(const orxOBJECT *_pstObject);

/** Gets object color.
 * @param[in]   _pstObject      Concerned object
 * @param[out]  _pstColor       Object's color
 * @return      orxCOLOR / orxNULL
 */
extern orxDLLAPI orxCOLOR *orxFASTCALL      orxObject_GetColor(const orxOBJECT *_pstObject, orxCOLOR *_pstColor);

/** Sets object RGB values.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvRGB          RGB values to set
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetRGB(orxOBJECT *_pstObject, const orxVECTOR *_pvRGB);

/** Sets color of an object and all its children.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _pvRGB          RGB values to set
 */
extern orxDLLAPI void orxFASTCALL           orxObject_SetRGBRecursive(orxOBJECT *_pstObject, const orxVECTOR *_pvRGB);

/** Sets object alpha.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fAlpha         Alpha value to set
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetAlpha(orxOBJECT *_pstObject, orxFLOAT _fAlpha);

/** Sets alpha of an object and all its children.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fAlpha         Alpha value to set
 */
extern orxDLLAPI void orxFASTCALL           orxObject_SetAlphaRecursive(orxOBJECT *_pstObject, orxFLOAT _fAlpha);


/** Sets object repeat (wrap) values.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fRepeatX       X-axis repeat value
 * @param[in]   _fRepeatY       Y-axis repeat value
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetRepeat(orxOBJECT *_pstObject, orxFLOAT _fRepeatX, orxFLOAT _fRepeatY);

/** Gets object repeat (wrap) values.
 * @param[in]   _pstObject     Concerned object
 * @param[out]  _pfRepeatX      X-axis repeat value
 * @param[out]  _pfRepeatY      Y-axis repeat value
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_GetRepeat(const orxOBJECT *_pstObject, orxFLOAT *_pfRepeatX, orxFLOAT *_pfRepeatY);


/** Sets object blend mode.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _eBlendMode     Blend mode (alpha, multiply, add or none)
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetBlendMode(orxOBJECT *_pstObject, orxDISPLAY_BLEND_MODE _eBlendMode);

/** Gets object blend mode.
 * @param[in]   _pstObject     Concerned object
 * @return Blend mode (alpha, multiply, add or none)
 */
extern orxDLLAPI orxDISPLAY_BLEND_MODE orxFASTCALL orxObject_GetBlendMode(const orxOBJECT *_pstObject);
/** @} */


/** @name Life time / active time
 * @{ */
/** Sets object lifetime.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _fLifeTime      Lifetime to set, negative value to disable it
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetLifeTime(orxOBJECT *_pstObject, orxFLOAT _fLifeTime);

/** Gets object lifetime.
 * @param[in]   _pstObject      Concerned object
 * @return      Lifetime / negative value if none
 */
extern orxDLLAPI orxFLOAT orxFASTCALL       orxObject_GetLifeTime(const orxOBJECT *_pstObject);

/** Gets object active time, i.e. the amount of time that the object has been alive taking into account
 * the object's clock multiplier and object's periods of pause.
 * @param[in]   _pstObject      Concerned object
 * @return      Active time
 */
extern orxDLLAPI orxFLOAT orxFASTCALL       orxObject_GetActiveTime(const orxOBJECT *_pstObject);
/** @} */

/** @name Group
 * @{ */
/** Gets default group ID.
 * @return      Default group ID
 */
extern orxDLLAPI orxU32 orxFASTCALL         orxObject_GetDefaultGroupID();

/** Gets object's group ID.
 * @param[in]   _pstObject      Concerned object
 * @return      Object's group ID. This is the string ID (see orxString_GetFromID()) of the object's group name.
 */
extern orxDLLAPI orxU32 orxFASTCALL         orxObject_GetGroupID(const orxOBJECT *_pstObject);

/** Sets object's group ID.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _u32GroupID     Group ID to set. This is the string ID (see orxString_GetID()) of the object's group name.
 * @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL      orxObject_SetGroupID(orxOBJECT *_pstObject, orxU32 _u32GroupID);

/** Sets group ID of an object and all its children.
 * @param[in]   _pstObject      Concerned object
 * @param[in]   _u32GroupID     Group ID to set. This is the string ID (see orxString_GetID()) of the object's group name.
 */
extern orxDLLAPI void orxFASTCALL           orxObject_SetGroupIDRecursive(orxOBJECT *_pstObject, orxU32 _u32GroupID);

/** Gets next object in group.
 * @param[in]   _pstObject      Concerned object, orxNULL to get the first one
 * @param[in]   _u32GroupID     Group ID to consider, orxU32_UNDEFINED for all
 * @return      orxOBJECT / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_GetNext(const orxOBJECT *_pstObject, orxU32 _u32GroupID);
/** @} */


/** @name Picking
 * @{ */
/** Picks the first active object with size "under" the given position, within a given group. See
 * orxObject_BoxPick(), orxObject_CreateNeighborList() and orxObject_Raycast for other ways of picking
 * objects.
 * @param[in]   _pvPosition     Position to pick from
 * @param[in]   _u32GroupID     Group ID to consider, orxU32_UNDEFINED for all
 * @return      orxOBJECT / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_Pick(const orxVECTOR *_pvPosition, orxU32 _u32GroupID);

/** Picks the first active object with size in contact with the given box, withing a given group. Use
 * orxObject_CreateNeighborList() to get all the objects in the box.
 * @param[in]   _pstBox         Box to use for picking
 * @param[in]   _u32GroupID     Group ID to consider, orxU32_UNDEFINED for all
 * @return      orxOBJECT / orxNULL
 */
extern orxDLLAPI orxOBJECT *orxFASTCALL     orxObject_BoxPick(const orxOBOX *_pstBox, orxU32 _u32GroupID);
/** @} */

#endif /* _orxOBJECT_H_ */

/** @} */