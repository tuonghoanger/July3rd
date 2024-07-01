#pragma once

#include "ChiliWin.h"
#include "Colors.h"
#include "Rect.h"
#include "ChiliException.h"
#include <string>
#include <assert.h>
#include <memory>

class Surface
{
public:
	class Exception : public ChiliException
	{
	public:
		using ChiliException::ChiliException;
		virtual std::wstring GetFullMessage() const override { return GetNote() + L"\nAt: " + GetLocation(); }
		virtual std::wstring GetExceptionType() const override { return L"Surface Exception"; }
	};
public:
	Surface(unsigned int width, unsigned int height)
		:
		Surface(width, height, width)
	{}
	Surface(unsigned int width, unsigned int height, unsigned int pitch)
		:
		pBuffer(std::make_unique<Color[]>(pitch* height)),
		width(width),
		height(height),
		pitch(pitch)
	{}
	Surface(Surface&& source)
		:
		pBuffer(std::move(source.pBuffer)),
		width(source.width),
		height(source.height),
		pitch(source.pitch)
	{}
	Surface(Surface&) = delete;
	Surface& operator=(Surface&& donor)
	{
		width = donor.width;
		height = donor.height;
		pitch = donor.pitch;
		pBuffer = std::move(donor.pBuffer);
		donor.pBuffer = nullptr;
		return *this;
	}
	Surface& operator=(const Surface&) = delete;
	~Surface()
	{}
	void Clear(Color fillValue)
	{
		memset(pBuffer.get(), fillValue.dword, pitch * height * sizeof(Color));
	}
	void Present(unsigned int dstPitch, BYTE* const pDst) const
	{
		for (unsigned int y = 0; y < height; y++)
		{
			memcpy(&pDst[dstPitch * y], &pBuffer[pitch * y], sizeof(Color) * width);
		}
	}
	void PutPixel(unsigned int x, unsigned int y, Color c)
	{
		assert(x >= 0);
		assert(y >= 0);
		assert(x < width);
		assert(y < height);
		pBuffer[y * pitch + x] = c;
	}
	void PutPixelAlpha(unsigned int x, unsigned int y, Color c);
	Color GetPixel(unsigned int x, unsigned int y) const
	{
		assert(x >= 0);
		assert(y >= 0);
		assert(x < width);
		assert(y < height);
		return pBuffer[y * pitch + x];
	}
	unsigned int GetWidth() const
	{
		return width;
	}
	unsigned int GetHeight() const
	{
		return height;
	}
	unsigned int GetPitch() const
	{
		return pitch;
	}
	Color* GetBufferPtr()
	{
		return pBuffer.get();
	}
	const Color* GetBufferPtrConst() const
	{
		return pBuffer.get();
	}
	static Surface FromFile(const std::wstring& name);
	void Save(const std::wstring& filename) const;
	void Copy(const Surface& src);
private:
	Surface(unsigned int width, unsigned int height, unsigned int pitch, std::unique_ptr<Color[]> pBufferParam)
		:
		width(width),
		height(height),
		pBuffer(std::move(pBufferParam)),
		pitch(pitch)
	{}
private:
	std::unique_ptr<Color[]> pBuffer;
	unsigned int width;
	unsigned int height;
	unsigned int pitch; // pitch is in PIXELS, not bytes!
};