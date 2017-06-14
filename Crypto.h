/*
// Synology DownloadStation Helper
//
// The application is designed to simplify adding your download tasks to DownloadStation on your Synology DiskStation.
//
// MIT License
//
// Copyright (c) 2017 xaozai
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
*/
#pragma once
#ifndef _CRYPTO_H_
#define _CRYPTO_H_

//	Include the standard cryptography header.
#include <Wincrypt.h>

	//	A simple class to wrap the Crypto API.
	class CCrypto
	{
	public:

		//	All of the Cryptography API initialisation is done in the 
		//	constructor, so constructing this object is expensive. I recommend having
		//	only one instance only, and keep it in your application class.
		CCrypto();
		virtual ~CCrypto();

		//	These functions are essential to using the crypto object- you must
		//	have a key from some source or other.

		//	Derive a key from a password.
		virtual bool DeriveKey(CString strPassword);

		//	These functions handle encryption and decryption.

		virtual bool Encrypt(const CObject& serializable, CByteArray& arData);
		virtual bool Decrypt(const CByteArray& arData, CObject& serializable);

		virtual bool Encrypt(const CString& str, CByteArray& arData);
		virtual bool Decrypt(const CByteArray& arData, CString& str);


	protected:

		//	Encrypt the contents of the memory file and store in the passed array.
		virtual bool InternalEncrypt(CByteArray& arDestination);

		//	Decrypt the contents of the passed array and store in the memory file.
		virtual bool InternalDecrypt(const CByteArray& arSource);

		//	Handle to the cryptography provider.
		HCRYPTPROV m_hCryptProv;
	
		//	Handle to the cryptography key.
		HCRYPTKEY m_hKey;

		//	Handle to the hash object.
		HCRYPTHASH m_hHash;

		//	Internally, the encryption and decryption of data is done with
		//	a CMemFile intermediate.
		CMemFile m_file;
	};

#endif