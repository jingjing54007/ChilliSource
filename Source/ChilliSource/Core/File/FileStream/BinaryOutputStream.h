//
//  The MIT License (MIT)
//
//  Copyright © 2016 Tag Games. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifndef _CHILLISOURCE_CORE_FILE_FILESTREAM_BINARYOUTPUTSTREAM_H_
#define _CHILLISOURCE_CORE_FILE_FILESTREAM_BINARYOUTPUTSTREAM_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Core/Base/ByteBuffer.h>

#include <fstream>

namespace ChilliSource
{
    /// Class to provide binary write functionality for a file
    ///
    /// Calling Write() on this stream will not cause a flush to disk, this will
    /// only occur when the destructer is called.
    ///
    /// If a BinaryOutputStream is created with an existing file, that file will
    /// be overwritten, regardless of whether or not a Write() was carried out
    ///
    /// BinaryOutputStream is thread agnostic, but not thread-safe.
    /// i.e. Instances can used by one thread at a time. It
    /// doesn't matter which thread as long as any previous threads
    /// are no longer accessing it
    ///
    class BinaryOutputStream final
    {
    public:
        
        CS_DECLARE_NOCOPY(BinaryOutputStream);
        
        /// This will create the filestream from the path passed in and evaluate if
        /// the stream is valid. After construction, IsValid() should be called to
        /// ensure the stream was created without errors before proceeding to call
        /// further functionality.
        ///
        /// @param filepath
        ///     The absolute path to a file
        ///
        BinaryOutputStream(const std::string& filePath) noexcept;
        
        /// Checks the status of the stream, if this returns false then the stream
        /// can no longer be accessed.
        ///
        /// @return If the stream is valid and available for use
        ///
        bool IsValid() const noexcept;
        
        /// Writes byte data to the stream. This will not effect contents
        /// on disk.
        ///
        /// Multiple calls to this function will append to any contents already
        /// written to the buffer.
        ///
        /// @param data
        ///		The string data to write to the stream
        /// @param length
        ///     The length of the data to write
        ///
        void Write(void* data, u64 length) noexcept;
        
        /// Writes ByteBuffer data to the stream. This will not effect contents
        /// on disk.
        ///
        /// Multiple calls to this function will append to any contents already
        /// written to the buffer.
        ///
        /// @param byteBuffer
        ///		The ByteBuffer object to write to the stream
        ///
        void Write(const ByteBufferUPtr& byteBuffer) noexcept;
        
        /// Writes POD data to the stream. This will not effect contents
        /// on disk.
        ///
        /// This will static_assert if TType is not a POD type
        ///
        /// Multiple calls to this function will append to any contents already
        /// written to the buffer.
        ///
        /// @param data
        ///		The POD data to write to the stream
        ///
        template<typename TType> void Write(TType data) noexcept;

        /// This will write any pending data written to this stream to disk
        /// and close the stream
        ///
        ~BinaryOutputStream() noexcept;
        
    private:
        
        bool m_isValid = false;
        std::ofstream m_fileStream;
    };
    //------------------------------------------------------------------------------
    template<typename TType> void BinaryOutputStream::Write(TType data) noexcept
    {
        static_assert(std::is_pod<TType>::value, "T must be POD type");
        
        CS_ASSERT(IsValid(), "Trying to use an invalid FileStream.");
        Write(&data, sizeof(TType));
        CS_ASSERT(!m_fileStream.fail(), "Unexpected error occured writing to the stream.");
    }
}

#endif
