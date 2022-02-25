/*
 * hashlib++ - a simple hash library for C++
 *
 * Copyright (c) 2007-2010 Benjamin Gr�delbach
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 	1)     Redistributions of source code must retain the above copyright
 * 	       notice, this list of conditions and the following disclaimer.
 *
 * 	2)     Redistributions in binary form must reproduce the above copyright
 * 	       notice, this list of conditions and the following disclaimer in
 * 	       the documentation and/or other materials provided with the
 * 	       distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//----------------------------------------------------------------------

/**
 * Changes by Anaxímeno Brito:								  [Feb 2022]
 *
 * 		This module was altered to turn it into a hpp module,
 *      all changes are under the same original license of the file
 * 		which could (in that moment) be found at:
 * 
 * 			http://hashlib2plus.sourceforge.net/index.html
 */

//----------------------------------------------------------------------

/**
 *  @file 	hl_sha512wrapper.h
 *  @brief	This file contains the definition of the sha512wrapper
 *  		class.
 *  @date 	Mo 12 Nov 2007
 */

//----------------------------------------------------------------------
//include protection
#ifndef SHA512WRAPPER_H
#define SHA512WRAPPER_H

//----------------------------------------------------------------------
//hashlib++ includes
#include "hl_hashwrapper.hpp"
#include "hl_sha2ext.hpp"

using namespace hlibpp_wrapper;
using namespace hlibpp_sha2ext;
//----------------------------------------------------------------------
//STL
#include <string>

//----------------------------------------------------------------------

namespace hlibpp_sha512_wrapper {
	/**
	 *  @brief 	This class represents the SHA512 wrapper-class
	 *
	 *  		You can use this class to easily create a sha512 hash.
	 *  		Just create an instance of sha512wrapper and call the
	 *  		inherited memberfunctions getHashFromString()
	 *  		and getHashFromFile() to create a hash based on a
	 *  		string or a file.
	 *
	 *  		Have a look at the following example:
	 *
	 *  @include 	sha512example.cpp
	 *
	 *  		sha512wrapper implements resetContext(), updateContext()
	 *  		and hashIt() to create a hash.
	 */
	class sha512wrapper : public hashwrapper
	{
		private:
				/**
				 * SHA512 access
				 * via extended SHA2
				 */
				SHA2ext *sha512;

				/**
				 * SHA512 context
				 */
				HL_SHA512_CTX context;

				/**
				 *  @brief 	This method ends the hash process
				 *  		and returns the hash as string.
				 *
				 *  @return 	a hash as std::string
				 */
				virtual std::string hashIt(void);

				/**
				 *  @brief 	This internal member-function
				 *  		convertes the hash-data to a
				 *  		std::string (HEX).
				 *
				 *  @param 	data The hash-data to covert into HEX
				 *  @return	the converted data as std::string
				 */
				virtual std::string convToString(unsigned char *data);

				/**
				 *  @brief 	This method adds the given data to the
				 *  		current hash context
				 *
				 *  @param 	data The data to add to the current context
				 *  @param 	len The length of the data to add
				 */
				virtual void updateContext(unsigned char *data, unsigned int len);

				/**
				 *  @brief 	This method resets the current hash context.
				 *  		In other words: It starts a new hash process.
				 */
				virtual void resetContext(void);

				/**
				 * @brief 	This method should return the hash of the
				 * 		test-string "The quick brown fox jumps over the lazy
				 * 		dog"
				 */
				virtual std::string getTestHash(void);

		public:

				/**
				 *  @brief 	default constructor
				 */
				sha512wrapper();

				/**
				 *  @brief 	default destructor
				 */
				virtual ~sha512wrapper();

	};

	/**
	 *  @brief 	This method ends the hash process
	 *  		and returns the hash as string.
	 *
	 *  @return 	a hash as std::string
	 */
	std::string sha512wrapper::hashIt(void)
	{
		sha2_byte buff[SHA512_DIGEST_STRING_LENGTH];
		sha512->SHA512_End(&context,(char*)buff);
		return convToString(buff);
	}

	/**
	 *  @brief 	This internal member-function
	 *  		convertes the hash-data to a
	 *  		std::string (HEX).
	 *
	 *  @param 	data The hash-data to covert into HEX
	 *  @return	the converted data as std::string
	 */
	std::string sha512wrapper::convToString(unsigned char *data)
	{
		/*
		 * we can just copy data to a string, because
		 * the transforming to hash is already done
		 * within the sha512 implementation
		 */
		return std::string((const char*)data);
	}

	/**
	 *  @brief 	This method adds the given data to the
	 *  		current hash context
	 *
	 *  @param 	data The data to add to the current context
	 *  @param 	len The length of the data to add
	 */
	void sha512wrapper::updateContext(unsigned char *data, unsigned int len)
	{
		this->sha512->SHA512_Update(&context,data,len);
	}

	/**
	 *  @brief 	This method resets the current hash context.
	 *  		In other words: It starts a new hash process.
	 */
	void sha512wrapper::resetContext(void)
	{
		sha512->SHA512_Init(&context);
	}

	/**
	 * @brief 	This method should return the hash of the
	 * 		test-string "The quick brown fox jumps over the lazy
	 * 		dog"
	 */
	std::string sha512wrapper::getTestHash(void)
	{
		return "07e547d9586f6a73f73fbac0435ed76951218fb7d0c8d788a309d785436bbb642e93a252a954f23912547d1e8a3b5ed6e1bfd7097821233fa0538f3db854fee6";
	}

	//----------------------------------------------------------------------
	//public memberfunctions

	/**
	 *  @brief 	default constructor
	 */
	sha512wrapper::sha512wrapper()
	{
		this->sha512 = new SHA2ext();
	}

	/**
	 *  @brief 	default destructor
	 */
	sha512wrapper::~sha512wrapper()
	{
		delete sha512;
	}
}
//----------------------------------------------------------------------
//end of include protection
#endif

//----------------------------------------------------------------------
//EOF
