## WinAPI Functions and Definitions

This Document Contains a list of Windows API information for all functions, definitions and types used in the project. All entries have been adapted from the Win32/Api documentation

*https://learn.microsoft.com/en-us/windows/win32/api*

## Functions {#comms}

### PurgeComm (winbase.h) {#purgecomm}

Discards all characters from the output or input buffer of a specified communications resource. It can also terminate pending read or write operations on the resource.

- Used For: Clearing all data on COM por when initializing in the **initPort** function in RS232Comm.cpp

#### Syntax:
```cpp
BOOL PurgeComm(
    [in] HANDLE hFile,
    [in] DWORD  dwFlags
);
```
#### Parameters:

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


### WriteFile (fileapi.h) {#writefile}

Writes data to a specified (I/O) device. can be used for COM ports and console ouput stream

- Used For: Data transmission over COM ports in function outputToPort RS232Comm.h, RS232Comm.cpp


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
: A handle to the file or I/O device (for example, a file, file stream, physical disk, volume, console buffer, tape drive, socket, communications resource, mailslot, or pipe). </p> The hFile parameter must have been created with the write access.

[in] lpBuffer
: A pointer to the buffer containing the data to be written to the file or device </p> This buffer must remain valid for the duration of the write operation. The caller must not use this buffer until the write operation is completed.

[in] nNumberOfBytesToWrite
: The number of bytes to be written to the file or device. </p> A value of zero specifies a null write operation. The behavior of a null write operation depends on the underlying file system or communications technology.

[out, optional] lpNumberOfBytesWritten
: A pointer to the variable that receives the number of bytes written when using a synchronous hFile parameter. WriteFile sets this value to zero before doing any work or error checking. Use NULL for this parameter if this is an asynchronous operation to avoid potentially erroneous results. </p> This parameter can be NULL only when the lpOverlapped parameter is not NULL. 

[in, out, optional] lpOverlapped
: A pointer to an OVERLAPPED structure is required if the hFile parameter was opened with **FILE_FLAG_OVERLAPPED**, otherwise this parameter can be NULL. </p> For an hFile that supports byte offsets, if you use this parameter you must specify a byte offset at which to start writing to the file or device. This offset is specified by setting the Offset and OffsetHigh members of the OVERLAPPED structure. For an hFile that does not support byte offsets, Offset and OffsetHigh are ignored. </p> To write to the end of file, specify both the Offset and OffsetHigh members of the OVERLAPPED structure as 0xFFFFFFFF. This is functionally equivalent to previously calling the CreateFile function to open hFile using **FILE_APPEND_DATA** access.

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

*- For more detailed info and examples see [WinApi Documentation](https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile)*

### ClearComError (winbase.h)(include Windows.h) {#clearcomerror}

Retrieves information about a communications error and reports the current status of a communications device. The function is called when a communications error occurs, and it clears the device's error flag to enable additional input and output (I/O) operations. 

##### Our Usage:
- clearing COM errors after assessing with GetLastError
    * see RS232Comm.cpp

#### Syntax:

```cpp
BOOL ClearCommError(
  [in]            HANDLE    hFile,
  [out, optional] LPDWORD   lpErrors,
  [out, optional] LPCOMSTAT lpStat
);
```

#### Parameters:

[in] hFile
: A handle to the communications device. The CreateFile function returns this handle.

[out, optional] lpErrors
: A pointer to a variable that receives a mask indicating the type of error. This parameter can be one or more of the following values.

|Value   |Meaning|
|---|---|
|**CE_BREAK**<br>0x0010|The hardware detected a break condition.|
|**CE_FRAME**<br>0x0008|The hardware detected a framing error.|
|**CE_OVERRUN**<br>0x0002|A character-buffer overrun has occurred. The next character is lost.|
|**CE_RXOVER**<br>0x0001|An input buffer overflow has occurred. There is either no room in the input buffer, or a character was received after the end-of-file (EOF) character.|
|**CE_RXPARITY**<br>0x0004|The hardware detected a parity error.|

The following values are not supported:

[out, optional] lpStat
: A pointer to a COMSTAT structure in which the device's status information is returned. If this parameter is NULL, no status information is returned.

#### Return Value
- On Success: non-zero
- On Failure: zero 
    * For extended error information, call GetLastError

#### Remarks
If a communications port has been set up with a **TRUE** value for the **fAbortOnError** member of the setup DCB structure, the communications software will terminate all read and write operations on the communications port when a communications error occurs. No new read or write operations will be accepted until the application acknowledges the communications error by calling the **ClearCommError** function.

### CreateFile (fileapi.h)(include Windows.h) {#createfile}

Creates or opens a file or I/O device. The most commonly used I/O devices are as follows: file, file stream, directory, physical disk, volume, console buffer, tape drive, communications resource, mailslot, and pipe. The function returns a handle that can be used to access the file or device for various types of I/O depending on the file or device and the flags and attributes specified.

- Used For: Opening device files for read/write operations to COM ports in function createPortFile in RS232Comms.cpp

```cpp
HANDLE CreateFileW(
  [in]           LPCWSTR               lpFileName,
  [in]           DWORD                 dwDesiredAccess,
  [in]           DWORD                 dwShareMode,
  [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [in]           DWORD                 dwCreationDisposition,
  [in]           DWORD                 dwFlagsAndAttributes,
  [in, optional] HANDLE                hTemplateFile
);
```

#### Parameters

[in] lpFileName
: The name of teh file or device to be created or opened. You may use either forward slashes (/) or backslashes (\) in this name.</p>For information on special device names, see [WinAPI - MS-DOS Device Names](https://learn.microsoft.com/en-us/windows/desktop/FileIO/defining-an-ms-dos-device-name)</p>To create a file stream, specify the name of the file, a colon, and then the name of the stream. For more information, see [WinAPI - File Streams](https://learn.microsoft.com/en-us/windows/desktop/FileIO/file-streams).

[in] dwDesiredAccess
: The requested access to the file or device, which can be summarized as read, write, both or neither zero).</p>The most commonly used values are **GENERIC_READ**, **GENERIC_WRITE**, or both (**GENERIC_READ** | **GENERIC_WRITE**). For more information, see [Generic Access Rights](https://learn.microsoft.com/en-us/windows/desktop/SecAuthZ/generic-access-rights), [File Security and Access Rights](https://learn.microsoft.com/en-us/windows/desktop/FileIO/file-security-and-access-rights), [File Access Rights Constants](https://learn.microsoft.com/en-us/windows/desktop/FileIO/file-access-rights-constants), and [ACCESS_MASK](https://learn.microsoft.com/en-us/windows/desktop/SecAuthZ/access-mask).</p>If this parameter is zero, the application can query certain metadata such as file, directory, or device attributes without accessing that file or device, even if **GENERIC_READ** access would have been denied.</p>You cannot request an access mode that conflicts with the sharing mode that is specified by the dwShareMode parameter in an open request that already has an open handle.

[in] dwShareMode
: The requested sharing mode of the file or device, which can be read, write, both, delete, all of these, or none (refer to the following table). Access requests to attributes or extended attributes are not affected by this flag.</p>If this parameter is zero and **CreateFile** succeeds, the file or device cannot be shared and cannot be opened again until the handle to the file or device is closed. For more information, see the Remarks section.</p>You cannot request a sharing mode that conflicts with the access mode that is specified in an existing request that has an open handle. **CreateFile** would fail and the [GetLastError](#getlasterror) function would return **ERROR_SHARING_VIOLATION**.</p>To enable a process to share a file or device while another process has the file or device open, use a compatible combination of one or more of the following values. For more information about valid combinations of this parameter with the dwDesiredAccess parameter, see [Creating and Opening Files](https://learn.microsoft.com/en-us/windows/desktop/FileIO/creating-and-opening-files).

|Value|Meaning|
|--|--|
|**0**<br>0x00000000|Prevents subsequent open operations on a file or device if they request delete, read, or write access.|
|**FILE_SHARE_DELETE**<br>0x00000004|Enables subsequent open operations on a file or device to request delete access.</p>Otherwise, no process can open the file or device if it requests delete access.</p>If this flag is not specified, but the file or device has been opened for delete access, the function fails.</p>**Note Delete access allows both delete and rename operations.|
|**FILE_SHARE_READ**<br>0x00000001|Enables subsequent open operations on a file or device to request read access.</p>Otherwise, no process can open the file or device if it requests read access.</p>If this flag is not specified, but the file or device has been opened for read access, the function fails.|
|**FILE_SHARE_WRITE**<br>0x00000002|Enables subsequent open operations on a file or device to request write access.</p>Otherwise, no process can open the file or device if it requests write access.</p>If this flag is not specified, but the file or device has been opened for write access or has a file mapping with write access, the function fails.|

[in, optional] lpSecurityAttributes
: A pointer to a **SECURITY_ATTRIBUTES** structure that contains two separate but related data members: an optional security descriptor, and a Boolean value that determines whether the returned handle can be inherited by child processes.</p>This parameter can be **NULL**.</p>If this parameter is **NULL**, the handle returned by **CreateFile** cannot be inherited by any child processes the application may create and the file or device associated with the returned handle gets a default security descriptor.</p>The **lpSecurityDescriptor** member of the structure specifies a **SECURITY_DESCRIPTOR** for a file or device. If this member is **NULL**, the file or device associated with the returned handle is assigned a default security descriptor.</p>CreateFile ignores the **lpSecurityDescriptor** member when opening an existing file or device, but continues to use the **bInheritHandle** member.</p>The **bInheritHandle** member of the structure specifies whether the returned handle can be inherited.

[in] dwCreationDisposition
: An action to take on a file or device that exists or does not exist.</p>For devices other than files, this parameter is usually set to **OPEN_EXISTING**.</p>This parameter must be one of the following values, which cannot be combined:

|Value|	Meaning|
|---|---|
|**CREATE_ALWAYS**<br>2|Creates a new file, always.</p>If the specified file exists and is writable, the function truncates the file, the function succeeds, and last-error code is set to **ERROR_ALREADY_EXISTS** (183).</p>If the specified file does not exist and is a valid path, a new file is created, the function succeeds, and the last-error code is set to zero.</p>For more information, see the Remarks section of this topic.|
|**CREATE_NEW**<br>1|Creates a new file, only if it does not already exist.</p>If the specified file exists, the function fails and the last-error code is set to **ERROR_FILE_EXISTS** (80).</p>If the specified file does not exist and is a valid path to a writable location, a new file is created|
|**OPEN_ALWAYS**<br>4|Opens a file, always.</p>If the specified file exists, the function succeeds and the last-error code is set to **ERROR_ALREADY_EXISTS** (183).</p>If the specified file does not exist and is a valid path to a writable location, the function creates a file and the last-error code is set to zero.|
|**OPEN_EXISTING**<br>3|Opens a file or device, only if it exists.</p>If the specified file or device does not exist, the function fails and the last-error code is set to **ERROR_FILE_NOT_FOUND** (2).|
|**TRUNCATE_EXISTING**<br>5|Opens a file and truncates it so that its size is zero bytes, only if it exists.</p>If the specified file does not exist, the function fails and the last-error code is set to **ERROR_FILE_NOT_FOUND** (2).</p>The calling process must open the file with the **GENERIC_WRITE** bit set as part of the dwDesiredAccess parameter.

[in] dwFlagsAndAttributes
: The file or device attributes and flags, **FILE_ATTRIBUTE_NORMAL** being the most common default value for files.</p>This parameter can include any combination of the available file attributes (**FILE_ATTRIBUTE_***). All other file attributes override **FILE_ATTRIBUTE_NORMAL**.</p>This parameter can also contain combinations of flags (**FILE_FLAG_**) for control of file or device caching behavior, access modes, and other special-purpose flags. These combine with any **FILE_ATTRIBUTE_** values.</p>This parameter can also contain Security Quality of Service (SQOS) information by specifying the **SECURITY_SQOS_PRESENT** flag. Additional SQOS-related flags information is presented in the table following the attributes and flags tables.</p>Note When CreateFile opens an existing file, it generally combines the file flags with the file attributes of the existing file, and ignores any file attributes supplied as part of dwFlagsAndAttributes. Special cases are detailed in Creating and Opening Files.</p>Some of the following file attributes and flags may only apply to files and not necessarily all other types of devices that CreateFile can open. For additional information, see the Remarks section of this topic and Creating and Opening Files.</p>For more advanced access to file attributes, see SetFileAttributes. For a complete list of all file attributes with their values and descriptions, see File Attribute Constants.

|Attribute|	Meaning|
|---|---|
|**FILE_ATTRIBUTE_ARCHIVE**<br>32 (0x20)|The file should be archived. Applications use this attribute to mark files for backup or removal.|
|**FILE_ATTRIBUTE_ENCRYPTED**<br>16384 (0x4000)|The file or directory is encrypted. For a file, this means that all data in the file is encrypted. For a directory, this means that encryption is the default for newly created files and subdirectories. For more information, see File Encryption.</p>This flag has no effect if **FILE_ATTRIBUTE_SYSTEM** is also specified.</p>This flag is not supported on Home, Home Premium, Starter, or ARM editions of Windows.|
|**FILE_ATTRIBUTE_HIDDEN**<br>2 (0x2)|The file is hidden. Do not include it in an ordinary directory listing.|
|**FILE_ATTRIBUTE_NORMAL**<br>128 (0x80)|The file does not have other attributes set. This attribute is valid only if used alone.|
|**FILE_ATTRIBUTE_OFFLINE**<br>4096 (0x1000)|The data of a file is not immediately available. This attribute indicates that file data is physically moved to offline storage. This attribute is used by Remote Storage, the hierarchical storage management software. Applications should not arbitrarily change this attribute.|
|**FILE_ATTRIBUTE_READONLY**<br>1 (0x1)|The file is read only. Applications can read the file, but cannot write to or delete it.|
|**FILE_ATTRIBUTE_SYSTEM**<br>4 (0x4)|The file is part of or used exclusively by an operating system.|
|**FILE_ATTRIBUTE_TEMPORARY**<br>256 (0x100)|
|The file is being used for temporary storage.|

|Flag	|Meaning|
|---|---|
|**FILE_FLAG_BACKUP_SEMANTICS**<br>0x02000000|The file is being opened or created for a backup or restore operation. The system ensures that the calling process overrides file security checks when the process has **SE_BACKUP_NAME** and **SE_RESTORE_NAME** privileges. For more information, see Changing Privileges in a Token.</p>You must set this flag to obtain a handle to a directory. A directory handle can be passed to some functions instead of a file handle. For more information, see the Remarks section.|
|**FILE_FLAG_DELETE_ON_CLOSE**<br>0x04000000|The file is to be deleted immediately after all of its handles are closed, which includes the specified handle and any other open or duplicated handles.</p>If there are existing open handles to a file, the call fails unless they were all opened with the **FILE_SHARE_DELETE** share mode.</p>Subsequent open requests for the file fail, unless the **FILE_SHARE_DELETE** share mode is specified.|
|**FILE_FLAG_NO_BUFFERING**<br>0x20000000|The file or device is being opened with no system caching for data reads and writes. This flag does not affect hard disk caching or memory mapped files.</p>There are strict requirements for successfully working with files opened with **CreateFile** using the **FILE_FLAG_NO_BUFFERING** flag, for details see File Buffering.|
|**FILE_FLAG_OPEN_NO_RECALL**<br>0x00100000|The file data is requested, but it should continue to be located in remote storage. It should not be transported back to local storage. This flag is for use by remote storage systems.|
|**FILE_FLAG_OPEN_REPARSE_POINT**<br>0x00200000|Normal reparse point processing will not occur; **CreateFile** will attempt to open the reparse point. When a file is opened, a file handle is returned, whether or not the filter that controls the reparse point is operational.
This flag cannot be used with the **CREATE_ALWAYS** flag.</p>If the file is not a reparse point, then this flag is ignored.|
|**FILE_FLAG_OVERLAPPED**<br>0x40000000|The file or device is being opened or created for asynchronous I/O.</p>When subsequent I/O operations are completed on this handle, the event specified in the OVERLAPPED structure will be set to the signaled state.</p>If this flag is specified, the file can be used for simultaneous read and write operations.</p>If this flag is not specified, then I/O operations are serialized, even if the calls to the read and write functions specify an OVERLAPPED structure.</p>For information about considerations when using a file handle created with this flag, see the Synchronous and Asynchronous I/O Handles section of this topic.|
|**FILE_FLAG_POSIX_SEMANTICS**<br>0x01000000|Access will occur according to POSIX rules. This includes allowing multiple files with names, differing only in case, for file systems that support that naming. Use care when using this option, because files created with this flag may not be accessible by applications that are written for MS-DOS or 16-bit Windows.|
|**FILE_FLAG_RANDOM_ACCESS**<br>0x10000000|Access is intended to be random. The system can use this as a hint to optimize file caching.</p>This flag has no effect if the file system does not support cached I/O and **FILE_FLAG_NO_BUFFERING**.|
|**FILE_FLAG_SESSION_AWARE**<br>0x00800000|The file or device is being opened with session awareness. If this flag is not specified, then per-session devices (such as a device using RemoteFX USB Redirection) cannot be opened by processes running in session 0. This flag has no effect for callers not in session 0. This flag is supported only on server editions of Windows.
Windows Server 2008 R2 and Windows Server 2008: This flag is not supported before Windows Server 2012.|
|**FILE_FLAG_SEQUENTIAL_SCAN**<br>0x08000000|Access is intended to be sequential from beginning to end. The system can use this as a hint to optimize file caching.</p>This flag should not be used if read-behind (that is, reverse scans) will be used.</p>This flag has no effect if the file system does not support cached I/O and **FILE_FLAG_NO_BUFFERING**.|
|**FILE_FLAG_WRITE_THROUGH**<br>0x80000000|Write operations will not go through any intermediate cache, they will go directly to disk.|

### GetLastError (errhandlingapi.h)(include Windows.h) {#getlasterror}

Retrieves the calling thread's last-error code value. The last-error code is maintained on a per-thread basis. Multiple threads do not overwrite each other's last-error code. 

```cpp
_Post_equals_last_error_ DWORD GetLastError();
```
#### Return Value

The return value is the calling thread's last-error code.

The Return Value section of the documentation for each function that sets the last-error code notes the conditions under which the function sets the last-error code. Most functions that set the thread's last-error code set it when they fail. However, some functions also set the last-error code when they succeed. If the function is not documented to set the last-error code, the value returned by this function is simply the most recent last-error code to have been set; some functions set the last-error code to 0 on success and others do not.

#### Remarks

Functions executed by the calling thread set this value by calling the [**SetLastError**](#setlasterror) function. You should call the **GetLastError** function immediately when a function's return value indicates that such a call will return useful data. That is because some functions call **SetLastError** with a zero when they succeed, wiping out the error code set by the most recently failed function.

To obtain an error string for system error codes, use the **FormatMessage** function. For a complete list of error codes provided by the operating system, see System Error Codes.

To convert a system error into an **HRESULT** value, use the **HRESULT_FROM_WIN32** macro.

*- For More info see [WinAPI Documentation](https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-getlasterror)*

## Datatypes {#types}

### LPCSTR {#lpcstr}

**LPCSTR** is a 32-bit pointer to a constant null-terminated string of 8-bit Windows (ANSI) characters. 

Not to be confused with the "wide" version [LPCWSTR](#lpcwstr)

### LPCWSTR {#lpwcstr}

An **LPCWSTR** is a 32-bit pointer to a constant string of 16-bit Unicode characters, which MAY be null-terminated.

Is effectively the "Wide" version of [LPCSTR](#lpcstr) as with **Wchar_t**. With certain API functions such as with the [CreateFile](#createfile) function (specifically CreateFileW) use of the following preprocessor directive is necessary:

```cpp
#define UNICODE
```

RS232Comms uses **LPCWSTR** in [CreateFile](#createfile) with the argument lpFileName. 

*- For more information on use of unicode characters see [CreateFile](#createfile)*

### GetCommState (winbase.h)(Windows.h) {#getcommstate}

Retireves the current control settings for a specified communications device.

##### Syntax:
```cpp
BOOL GetCommState(
  [in]      HANDLE hFile,
  [in, out] LPDCB  lpDCB
);
```



### DCB Structure (winbase.h)(Windows.h) {#DCB}

**DCB** Defines control settings for a serial communications device.

RS232Comms uses 

#### Syntax

```cpp
typedef struct _DCB {
  DWORD DCBlength;
  DWORD BaudRate;
  DWORD fBinary : 1;
  DWORD fParity : 1;
  DWORD fOutxCtsFlow : 1;
  DWORD fOutxDsrFlow : 1;
  DWORD fDtrControl : 2;
  DWORD fDsrSensitivity : 1;
  DWORD fTXContinueOnXoff : 1;
  DWORD fOutX : 1;
  DWORD fInX : 1;
  DWORD fErrorChar : 1;
  DWORD fNull : 1;
  DWORD fRtsControl : 2;
  DWORD fAbortOnError : 1;
  DWORD fDummy2 : 17;
  WORD  wReserved;
  WORD  XonLim;
  WORD  XoffLim;
  BYTE  ByteSize;
  BYTE  Parity;
  BYTE  StopBits;
  char  XonChar;
  char  XoffChar;
  char  ErrorChar;
  char  EofChar;
  char  EvtChar;
  WORD  wReserved1;
} DCB, *LPDCB;
```

#### Members

DCBlength
: the length of the structure, in bytes. The caller must set this member to **sizeof**(DCB)

BaudRate
: The baud rate at which the communications device operates. This member can be an actual baud rate value, or one of the following indexes.

|Value|Meaning|
|---|---|
|**CBR_110**<br>110|110 bps|
|**CBR_300**<br>300|300 bps|
|**CBR_600**<br>600|600 bps|
|**CBR_1200**<br>1200|1200 bps|
|**CBR_2400**<br>2400|2400 bps|
|**CBR_4800**<br>4800|4800 bps|
|**CBR_9600**<br>9600|9600 bps|
|**CBR_14400**<br>14400|14400 bps|
|**CBR_19200**<br>19200|19200 bps|
|**CBR_38400**<br>38400|38400 bps|
|**CBR_57600**<br>57600|57600 bps|
|**CBR_115200**<br>115200|115200 bps|
|**CBR_128000**<br>128000|128000 bps|
|**CBR_256000**<br>256000|256000 bps|

fBinary
: If this member is **TRUE**, binary mode is enabled. Windows does not support nonbinary mode transfers, so this member must be TRUE.

fParity
: If this member is **TRUE**, parity checking is performed and errors are reported.

fOutxCtsFlow
: If this member is **TRUE**, the **CTS** (clear-to-send) signal is monitored for output flow control. If this member is **TRUE** and **CTS** is turned off, output is suspended until **CTS** is sent again.

fOutxDsrFlow
: If this member is **TRUE**, the **DSR** (data-set-ready) signal is monitored for output flow control. If this member is **TRUE** and **DSR** is turned off, output is suspended until **DSR** is sent again.

fDtrControl
: The **DTR** (data-terminal-ready) flow control. This member can be one of the following values.

| Value | Meaning |
|---|---|
|**DTR_CONTROL_DISABLE**<br>0x00|Disables the **DTR** line when the device is opened and leaves it disabled.|
|**DTR_CONTROL_ENABLE**<br>0x01|Enables the **DTR** line when the device is opened and leaves it on.|
|**DTR_CONTROL_HANDSHAKE**<br>0x02|Enables **DTR** handshaking. If handshaking is enabled, it is an error for the application to adjust the line by using the **EscapeCommFunction** function.|

fDsrSensitivity
: If this member is **TRUE**, the communications driver is sensitive to the state of the DSR signal. The driver ignores any bytes received, unless the DSR modem input line is high.

fTXContinueOnXoff
: If this member is **TRUE**, transmission continues after the input buffer has come within **XoffLim** bytes of being full and the driver has transmitted the **XoffChar** character to stop receiving bytes. If this member is **FALSE**, transmission does not continue until the input buffer is within **XonLim** bytes of being empty and the driver has transmitted the **XonChar** character to resume reception.

fOutX
: Indicates whether **XON/XOFF** flow control is used during transmission. If this member is **TRUE**, transmission stops when the **XoffChar** character is received and starts again when the **XonChar** character is received.

fInX
: Indicates whether **XON/XOFF** flow control is used during reception. If this member is **TRUE**, the **XoffChar** character is sent when the input buffer comes within **XoffLim** bytes of being full, and the XonChar character is sent when the input buffer comes within **XonLim** bytes of being empty.

fErrorChar
: Indicates whether bytes received with parity errors are replaced with the character specified by the **ErrorChar** member. If this member is **TRUE** and the **fParity** member is **TRUE**, replacement occurs.

fNull
: If this member is **TRUE**, null bytes are discarded when received.

fRtsControl
: The **RTS** (request-to-send) flow control. This member can be one of the following values.

|Value|	Meaning|
|---|---|
|**RTS_CONTROL_DISABLE**<br>0x00|Disables the RTS line when the device is opened and leaves it disabled.|
|**RTS_CONTROL_ENABLE**<br>0x01|Enables the RTS line when the device is opened and leaves it on.|
|**RTS_CONTROL_HANDSHAKE**<br>0x02|Enables RTS handshaking. The driver raises the RTS line when the "type-ahead" (input) buffer is less than one-half full and lowers the RTS line when the buffer is more than three-quarters full. If handshaking is enabled, it is an error for the application to adjust the line by using the **EscapeCommFunction** function.|
|**RTS_CONTROL_TOGGLE**<br>0x03|Specifies that the RTS line will be high if bytes are available for transmission. After all buffered bytes have been sent, the RTS line will be low.|

fAbortOnError
: If this member is TRUE, the driver terminates all read and write operations with an error status if an error occurs. The driver will not accept any further communications operations until the application has acknowledged the error by calling the [ClearCommError](#clearcomerror) function.

fDummy2
: Reserved; do not use.

wReserved
: Reserved; must be zero.

XonLim
: The minimum number of bytes in use allowed in the input buffer before flow control is activated to allow transmission by the sender. This assumes that either **XON/XOFF**, RTS, or DTR input flow control is specified in the **fInX**, **fRtsControl**, or **fDtrControl** members.

XoffLim
: The minimum number of free bytes allowed in the input buffer before flow control is activated to inhibit the sender. Note that the sender may transmit characters after the flow control signal has been activated, so this value should never be zero. This assumes that either **XON/XOFF**, RTS, or DTR input flow control is specified in the **fInX**, **fRtsControl**, or **fDtrControl** members. The maximum number of bytes in use allowed is calculated by subtracting this value from the size, in bytes, of the input buffer.

ByteSize
: The number of bits in the bytes transmitted and received.

Parity
: The parity scheme to be used. This member can be one of the following values.

|Value|Meaning|
|---|---|
|**EVENPARITY**<br>2|Even parity.|
|**MARKPARITY**<br>3|Mark parity.|
|**NOPARITY**<br>0|No parity.|
|**ODDPARITY**<br>1|Odd parity.|
|**SPACEPARITY**<br>4|Space parity.|

StopBits
: The number of stop bits to be used. This member can be one of the following values.

|Value|Meaning|
|---|---|
|**ONESTOPBIT**<br>0|1 stop bit.|
|**ONESTOPBITS**<br>1|1.5 stop bits.|
|**TWOSTOPBITS**<br>2|2 stop bits.|

XonChar
: The value of the XON character for both transmission and reception.

XoffChar
: The value of the XOFF character for both transmission and reception.

ErrorChar
: The value of the character used to replace bytes received with a parity error.

EofChar
: The value of the character used to signal the end of data.

EvtChar
: The value of the character used to signal an event.

wReserved1
: Reserved; do not use.

