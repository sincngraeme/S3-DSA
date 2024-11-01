## WinAPI Functions and Definitions

This Document Contains a list of Windows API information for all functions, definitions and types used in the project. All entries have been adapted from the Win32/Api documentation

*https://learn.microsoft.com/en-us/windows/win32/api*

## COMMS 

### PurgeComm (winbase.h) 

#### Syntax:
```cpp
BOOL PurgeComm(
    [in] HANDLE hFile,
    [in] DWORD  dwFlags
);
```
#### Paramteters:

[in] hFile
: A handle to the communications resource. The CreateFile function returns this handle.

[in] dwFlags
: This parameter can be one or more of the following values.

| Value|Meaning  |
|---|---|
|**PURGE_RXABORTA**<br>0x0002|   Terminates all outstanding overlapped read operations and returns imediately even if the read operations have not been completed>|
|**PURGE_RXCLEAR** <br>0x0008|   Clears the input buffer (if the device driver has one). |
|**PURGE_TXABORT** <br>0x0001|   Terminates all outstanding overlapped write operations and returns immediately, even if the write operations have not been completed.
|**PURGE_TXCLEAR** <br>0x0004|   Clears the output buffer (if the device driver has one).|

#### Return Value:

- non-zero on success
- zero on failiure - call GetLastError for extended error information


### WriteFile (fileapi.h)

Writes data to a specified (I/O) device. can be used for COM ports and console ouput stream

#### Syntax:

```cpp
BOOL WriteFile(
  [in]                HANDLE       hFile,
  [in]                LPCVOID      lpBuffer,
  [in]                DWORD        nNumberOfBytesToWrite,
  [out, optional]     LPDWORD      lpNumberOfBytesWritten,
  [in, out, optional] LPOVERLAPPED lpOverlapped
);
```

#### Paramters

[in] hFile
: A handle to the file or I/O device (for example, a file, file stream, physical disk, volume, console buffer, tape drive, socket, communications resource, mailslot, or pipe). <br><br> The hFile parameter must have been created with the write access.

[in] lpBuffer
: A pointer to the buffer containing the data to be written to the file or device <br><br> This buffer must remain valid for the duration of the write operation. The caller must not use this buffer until the write operation is completed.

[in] nNumberOfBytesToWrite
: The number of bytes to be written to the file or device. <br><br> A value of zero specifies a null write operation. The behavior of a null write operation depends on the underlying file system or communications technology.

[out, optional] lpNumberOfBytesWritten
: A pointer to the variable that receives the number of bytes written when using a synchronous hFile parameter. WriteFile sets this value to zero before doing any work or error checking. Use NULL for this parameter if this is an asynchronous operation to avoid potentially erroneous results. <br><br> This parameter can be NULL only when the lpOverlapped parameter is not NULL. 

[in, out, optional] lpOverlapped
: A pointer to an OVERLAPPED structure is required if the hFile parameter was opened with **FILE_FLAG_OVERLAPPED**, otherwise this parameter can be NULL. <br><br> For an hFile that supports byte offsets, if you use this parameter you must specify a byte offset at which to start writing to the file or device. This offset is specified by setting the Offset and OffsetHigh members of the OVERLAPPED structure. For an hFile that does not support byte offsets, Offset and OffsetHigh are ignored. <br><br> To write to the end of file, specify both the Offset and OffsetHigh members of the OVERLAPPED structure as 0xFFFFFFFF. This is functionally equivalent to previously calling the CreateFile function to open hFile using **FILE_APPEND_DATA** access.

#### Return Value

- If the function succeeds, the return value is nonzero (TRUE).

- If the function fails, or is completing asynchronously, the return value is zero (FALSE). To get extended error information, call the GetLastError function.

#### Remarks

The function returns on the following conditions

- The number of bytes requested is written.
- A read operation releases buffer space on the read end of the pipe (if the write was blocked). For more information, see the Pipes section.
An asynchronous handle is being used and the write is occurring asynchronously.
- An error occurs.
- The WriteFile function may fail with **ERROR_INVALID_USER_BUFFER** or **ERROR_NOT_ENOUGH_MEMORY** whenever there are too many outstanding asynchronous I/O requests.

To cancel all pending asynchronous I/O operations, use either:

- **CancelIo**—this function cancels only operations issued by the calling thread for the specified file handle.
- **CancelIoEx**—this function cancels all operations issued by the threads for the specified file handle.

Use the **CancelSynchronousIo** function to cancel pending synchronous I/O operations.

I/O operations that are canceled complete with the error **ERROR_OPERATION_ABORTED**.

Characters can be written to screen buffer using **WriteFile** with a handle to a console output

** When writing to comms device, behaviour is determined by communication timeout (see GetComTimeouts and SetComTimeouts)

#### Our Usage:

Used for data transmission over COM ports
- see RS232Comm.h, RS232Comm.cpp


*- For more detailed info and examples see [WinApi Documentation](https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile)*


### ClearComError (winbase.h)



