#pragma once
/*!
File: GLog.h
Purpose: A Gateware interface that handles logging in a thread safe manner
Author: Justin W. Parks
Contributors: N/A
Last Modified: 10/30/2016
Copyright: 7thGate Software LLC.
License: MIT
*/

// GFile Inherits directly from GMultiThreaded 
#include "../G_Core/GMultiThreaded.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong
namespace GW
{
	//! The core namespace to which all Gateware fundamental interfaces must belong.
	namespace CORE
	{
		//! Unique Identifier for this interface. {79AC4197-1A78-4A86-A4A4-E84773A2F6DF}
		static const GUUIID GLogUUIID =
		{
			0x79ac4197, 0x1a78, 0x4a86,{ 0xa4, 0xa4, 0xe8, 0x47, 0x73, 0xa2, 0xf6, 0xdf }
		};

		//Forward declaration so we can use GFile* in a function
		class GFile;

		/*! The GLog class
		*
		*  This class will use a queue to keep track of any logged messages. The actual write out of the logs
		*  will be done in a seperate low priority worker thread. This thread will be set to check the queue every 2 seconds.
		*  This will keep the number of mutex locks to a bare minimum while maintaining thread safety. The maximum size of the
		*  queue will be 20 and a function is provided to force a write. When logs are wrote out the queue is emptied.
		*
		*/
		class GLog : public GMultiThreaded
		{
			// All Gateware API interfaces contain no variables & are pure virtual
		public:

			/*! Logs a null terminated string.
			*
			*  Date, Time, and thread ID will be appended to the front of the message unless specified otherwise (See EnableVerboseLogging).
			*  A new line character will be appended to the end of the string so your log messages do not require a new line.
			*
			*  @param [in] _log The message to log out.
			*
			*  @retval SUCCESS  Successfully queued the message to the log.
			*  @return FAILURE  The queue has reached maximun size (call flush). 
			*/
			virtual GRETURN Log(const char* const _log) = 0;
			
			/*! Logs a null terminated string with a category.
			*
			*  Date, Time, and thread ID will be appended to the front of the message unless specified otherwise (See EnableVerboseLogging).
			*  A new line character will be appended to the end of the string so your log messages do not require a new line.
			*
			*  @param [in] _category The category the log belongs in. ie. ERROR, WARNING, INFO, etc.
			*  @param [in] _log The message to log out.
			*
			*  @retval SUCCESS  Successfully queued the message to the log.
			*  @return FAILURE  The queue has reached maximun size (call flush).
			*/
			virtual GRETURN LogCatergorized(const char* const _category, const char* const _log) = 0;
			
			/*! Turns verbose logging on or off.
			*
			*  Use this function to prevent the addition of date, time, and threadID to your logs.
			*
			*  @param [in] _value true to turn on or false to turn off.
			*
			*/
			virtual void EnableVerboseLogging(bool _value) = 0;
			
			/*! Forces a log dump to file.
			*
			*  This will force a log dump to the file and clear the log queue.
			*
			*
			*  @retval SUCCESS  Successfully dumped the logs
			*  @return FAILURE  Most likely a file corruption or a file is not open.
			*/
			virtual GRETURN Flush() = 0;

			/*! Forces a log dump to file and closes the log file.
			*
			*  This needs to be called on all log files before shutdown so a shutdown
			*  message can be sent to their worker threads.
			*
			*  @retval SUCCESS  Successfully dumped the logs and closed the thread.
			*  @return FAILURE  Most likely a file corruption or a file is not open.
			*/
			virtual GRETURN CloseLogs() = 0;
		};

		/*! Creates a GLog object
		*
		*  This function will create a GLog object with the log file being created in the directory
		*  the program was ran from. If you want to control where the log file is going to be created at
		*  then use the overridden function to pass in a GFile* that is pre set the way you want it.
		*
		*  @param [in] _fileName The name of the log file.
		*  @param [out] _outLog Will contain the GLog if succefully created.
		*
		*  @retval SUCCESS  GLog was successfully created.
		*  @return FAILURE  GLog was not created. _outLog will be null
		*/
		GRETURN GCreateLog(const char* const _fileName, GLog** _outLog);

		/*! Creates a GLog object
		*
		*  This function will create a GLog object with the GFile object that was passed in.
		*  This is so you can have more control over your log by setting up a GFile in advance.
		*  The GFile object should already have a file open for text writing.
		*  NOTE: A reference count will be added to the GFile object passed in if the function succeeds.
		*
		*  @param [in] _file The GFile object that this log will use.
		*  @param [out] _outLog Will contain the GLog if succefully created.
		*
		*  @retval SUCCESS  GLog was successfully created.
		*  @return FAILURE  GLog was not created. _outLog will be null
		*/
		GRETURN GCreateLog(GFile* _file, GLog** _outLog);
	}
}