 // The following are message definitions.
//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: ERROR_MESSAGE
//
// MessageText:
//
// %1 [%2]: %3
//
#define ERROR_MESSAGE                    ((DWORD)0x00000001L)

//
// MessageId: WARNING_MESSAGE
//
// MessageText:
//
// %1 [%2]: %3
//
#define WARNING_MESSAGE                  ((DWORD)0x00000002L)

//
// MessageId: INFO_MESSAGE
//
// MessageText:
//
// %1 [%2]: %3
//
#define INFO_MESSAGE                     ((DWORD)0x00000003L)

 // A message file must end with a period on its own line
 // followed by a blank line.