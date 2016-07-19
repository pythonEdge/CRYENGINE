// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.

// -------------------------------------------------------------------------
//  Created:     28/07/2015 by Filipe amim
//  Description:
// -------------------------------------------------------------------------
//
////////////////////////////////////////////////////////////////////////////

namespace pfx2
{

//////////////////////////////////////////////////////////////////////////
// Streams

ILINE IFStream::IFStream(const float* pStream, float defaultVal)
	: m_safeSink(ToFloatv(defaultVal))
	, m_pStream(pStream ? pStream : (float*)&m_safeSink)
	, m_safeMask(pStream ? ~0 : 0)
{
}

ILINE float IFStream::Load(TParticleId pId) const
{
	return *(m_pStream + pId);
}

ILINE float IFStream::Load(TParticleId pId, float defaultVal) const
{
	return (pId != gInvalidId) ? *(m_pStream + pId) : defaultVal;
}

ILINE float IFStream::SafeLoad(TParticleId pId) const
{
	return *(m_pStream + (pId & m_safeMask));
}

ILINE IOFStream::IOFStream(float* pStream)
	: m_pStream(pStream)
{
}

ILINE float IOFStream::Load(TParticleId pId) const
{
	return *(m_pStream + pId);
}

ILINE void IOFStream::Store(TParticleId pId, float value)
{
	*(m_pStream + pId) = value;
}

ILINE IVec3Stream::IVec3Stream(const float* pX, const float* pY, const float* pZ, Vec3 defaultVal)
	: m_safeSink(ToFloatv(defaultVal.x), ToFloatv(defaultVal.y), ToFloatv(defaultVal.z))
	, m_pXStream((pX && pY && pZ) ? pX : (float*)&m_safeSink.x)
	, m_pYStream((pX && pY && pZ) ? pY : (float*)&m_safeSink.y)
	, m_pZStream((pX && pY && pZ) ? pZ : (float*)&m_safeSink.z)
	, m_safeMask((pX && pY && pZ) ? ~0 : 0)
{
}

ILINE Vec3 IVec3Stream::Load(TParticleId pId) const
{
	return Vec3(*(m_pXStream + pId), *(m_pYStream + pId), *(m_pZStream + pId));
}

ILINE Vec3 IVec3Stream::SafeLoad(TParticleId pId) const
{
	return Vec3(
	  *(m_pXStream + (pId & m_safeMask)),
	  *(m_pYStream + (pId & m_safeMask)),
	  *(m_pZStream + (pId & m_safeMask)));
}

ILINE IOVec3Stream::IOVec3Stream(float* pX, float* pY, float* pZ)
	: m_pXStream(pX)
	, m_pYStream(pY)
	, m_pZStream(pZ)
{
}

ILINE Vec3 IOVec3Stream::Load(TParticleId pId) const
{
	return Vec3(
	  *(m_pXStream + pId),
	  *(m_pYStream + pId),
	  *(m_pZStream + pId));
}

ILINE void IOVec3Stream::Store(TParticleId pId, Vec3 value)
{
	*(m_pXStream + pId) = value.x;
	*(m_pYStream + pId) = value.y;
	*(m_pZStream + pId) = value.z;
}

ILINE IQuatStream::IQuatStream(const float* pX, const float* pY, const float* pZ, const float* pW, Quat defaultVal)
	: m_safeSink(defaultVal)
	, m_pXStream((pX && pY && pZ && pW) ? pX : (float*)&m_safeSink.v.x)
	, m_pYStream((pX && pY && pZ && pW) ? pY : (float*)&m_safeSink.v.y)
	, m_pZStream((pX && pY && pZ && pW) ? pZ : (float*)&m_safeSink.v.z)
	, m_pWStream((pX && pY && pZ && pW) ? pW : (float*)&m_safeSink.w)
	, m_safeMask((pX && pY && pZ && pW) ? ~0 : 0)
{
}

ILINE Quat IQuatStream::Load(TParticleId pId) const
{
	return Quat(
	  *(m_pWStream + pId),
	  *(m_pXStream + pId),
	  *(m_pYStream + pId),
	  *(m_pZStream + pId));
}

ILINE Quat IQuatStream::SafeLoad(TParticleId pId) const
{
	return Quat(
	  *(m_pWStream + (pId & m_safeMask)),
	  *(m_pXStream + (pId & m_safeMask)),
	  *(m_pYStream + (pId & m_safeMask)),
	  *(m_pZStream + (pId & m_safeMask)));
}

ILINE IOQuatStream::IOQuatStream(float* pX, float* pY, float* pZ, float* pW)
	: m_pXStream(pX)
	, m_pYStream(pY)
	, m_pZStream(pZ)
	, m_pWStream(pW)
{
}

ILINE Quat IOQuatStream::Load(TParticleId pId) const
{
	return Quat(
	  *(m_pWStream + pId),
	  *(m_pXStream + pId),
	  *(m_pYStream + pId),
	  *(m_pZStream + pId));
}

ILINE void IOQuatStream::Store(TParticleId pId, Quat value)
{
	*(m_pWStream + pId) = value.w;
	*(m_pXStream + pId) = value.v.x;
	*(m_pYStream + pId) = value.v.y;
	*(m_pZStream + pId) = value.v.z;
}

ILINE IOColorStream::IOColorStream(UCol* pStream)
	: m_pStream(pStream)
{
}

ILINE UCol IOColorStream::Load(TParticleId pId) const
{
	return *(m_pStream + pId);
}

ILINE void IOColorStream::Store(TParticleId pId, UCol value)
{
	*(m_pStream + pId) = value;
}

template<typename T, typename Tv>
ILINE TIStream<T, Tv>::TIStream(const T* pStream, const T& defaultVal)
	: m_safeSink(defaultVal)
	, m_pStream(pStream ? pStream : &m_safeSink)
	, m_safeMask(pStream ? ~0 : 0)
{
}

template<typename T, typename Tv>
ILINE TIStream<T, Tv>::TIStream(const TIStream<T, Tv>& src)
	: m_safeSink(src.m_safeSink)
	, m_pStream(src.m_pStream)
	, m_safeMask(src.m_safeMask)
{
}

template<typename T, typename Tv>
ILINE TIStream<T, Tv>& TIStream<T, Tv >::operator=(const TIStream<T, Tv>& src)
{
	m_safeSink = src.m_safeSink;
	m_pStream = src.m_pStream;
	m_safeMask = src.m_safeMask;
	return *this;
}

template<typename T, typename Tv>
ILINE T TIStream<T, Tv >::Load(TParticleId pId) const
{
	return *(m_pStream + pId);
}

template<typename T, typename Tv>
ILINE T TIStream<T, Tv >::Load(TParticleId pId, T defaultVal) const
{
	return (pId != gInvalidId) ? *(m_pStream + pId) : defaultVal;
}

template<typename T, typename Tv>
ILINE T TIStream<T, Tv >::SafeLoad(TParticleId pId) const
{
	return *(m_pStream + (pId & m_safeMask));
}

template<typename T>
ILINE TIOStream<T>::TIOStream(T* pStream)
	: m_pStream(pStream)
{
}

template<typename T>
ILINE T TIOStream<T >::Load(TParticleId pId) const
{
	return *(m_pStream + pId);
}

template<typename T>
ILINE void TIOStream<T >::Store(TParticleId pId, T value)
{
	*(m_pStream + pId) = value;
}

//////////////////////////////////////////////////////////////////////////
// Functions

ILINE floatv Frac(floatv f)
{
	return f - floor(f);
}

// Vector functions

ILINE Vec3 HMin(const Vec3v& v0)
{
	return Vec3(
	  HMin(v0.x),
	  HMin(v0.y),
	  HMin(v0.z));
}

ILINE Vec3 HMax(const Vec3v& v0)
{
	return Vec3(
	  HMax(v0.x),
	  HMax(v0.y),
	  HMax(v0.z));
}

ILINE Vec3v Add(const Vec3v& a, floatv b)
{
	return Vec3v(a.x + b, a.y + b, a.z + b);
}
ILINE Vec3v Sub(const Vec3v& a, floatv b)
{
	return Vec3v(a.x - b, a.y - b, a.z - b);
}

template<typename T>
ILINE Vec3_tpl<T> MAdd(const Vec3_tpl<T>& a, const Vec3_tpl<T>& b, const Vec3_tpl<T>& c)
{
	return Vec3_tpl<T>(
	  MAdd(a.x, b.x, c.x),
	  MAdd(a.y, b.y, c.y),
	  MAdd(a.z, b.z, c.z));
}

template<typename T>
ILINE Vec3_tpl<T> MAdd(const Vec3_tpl<T>& a, T b, const Vec3_tpl<T>& c)
{
	return Vec3_tpl<T>(
	  MAdd(a.x, b, c.x),
	  MAdd(a.y, b, c.y),
	  MAdd(a.z, b, c.z));
}

ILINE floatv DeltaTime(floatv normAge, floatv frameTime)
{
	return __fsel(normAge, frameTime, -(normAge * frameTime));
}

ILINE uint8 FloatToUFrac8Saturate(float v)
{
	return uint8(saturate(v) * 255.0f + 0.5f);
}

ILINE ColorF ToColorF(UCol color)
{
	return ColorF(
	  ufrac8_to_float(color.r),
	  ufrac8_to_float(color.g),
	  ufrac8_to_float(color.b));
}

ILINE ColorFv ToColorFv(ColorF color)
{
	return ColorFv(
	  ToFloatv(color.r),
	  ToFloatv(color.g),
	  ToFloatv(color.b));
}

ILINE UCol ColorFToUCol(const ColorF& color)
{
	UCol result;
	result.r = float_to_ufrac8(color.r);
	result.g = float_to_ufrac8(color.g);
	result.b = float_to_ufrac8(color.b);
	result.a = 0xff;
	return result;
}

ILINE void RotateAxes(Vec3* v0, Vec3* v1, float angle)
{
	CRY_PFX2_ASSERT(v0 && v1);
	Vec2 vRot;
	sincos(angle, &vRot.x, &vRot.y);
	Vec3 vXAxis = *v0 * vRot.y - *v1 * vRot.x;
	Vec3 vYAxis = *v0 * vRot.x + *v1 * vRot.y;
	*v0 = vXAxis;
	*v1 = vYAxis;
}

}

#ifdef CRY_PFX2_USE_SSE
	#include "ParticleMathImplSSE.h"
#else

// PFX2_TODO : move all of this to another file (or just implement NEON for once)
namespace pfx2
{

ILINE floatv ToFloatv(float v)
{
	return v;
}

ILINE uint32v ToUint32v(uint32 v)
{
	return v;
}

ILINE floatv ToFloatv(int32v v)
{
	return floatv(v);
}

ILINE Vec3v ToVec3v(Vec3 v)
{
	return v;
}

ILINE Vec4v ToVec4v(Vec4 v)
{
	return v;
}

ILINE Planev ToPlanev(Plane v)
{
	return v;
}

ILINE float HMin(floatv v0)
{
	return v0;
}

ILINE float HMax(floatv v0)
{
	return v0;
}

ILINE ColorFv ToColorFv(UColv color)
{
	return ColorFv(
	  ufrac8_to_float(color.r),
	  ufrac8_to_float(color.g),
	  ufrac8_to_float(color.b));
}

ILINE UColv ColorFvToUColv(const ColorFv& color)
{
	UColv result;
	result.r = float_to_ufrac8(color.r);
	result.g = float_to_ufrac8(color.g);
	result.b = float_to_ufrac8(color.b);
	result.a = 0xff;
	return result;
}

ILINE UColv ToUColv(UCol color)
{
	return color;
}


}

#endif
