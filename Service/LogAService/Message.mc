MessageIdTypedef=DWORD

SeverityNames=(Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
    Warning=0x2:STATUS_SEVERITY_WARNING
    Error=0x3:STATUS_SEVERITY_ERROR
    )

LanguageNames=(English=0x409:MSG00409)

; // The following are message definitions.

MessageId=0x1
Severity=Error
SymbolicName=ERROR_MESSAGE
Language=English
%1 [%2]: %3
.

MessageId=0x2
Severity=Warning
SymbolicName=WARNING_MESSAGE
Language=English
%1 [%2]: %3
.

MessageId=0x3
Severity=Informational
SymbolicName=INFO_MESSAGE
Language=English
%1 [%2]: %3
.

; // A message file must end with a period on its own line
; // followed by a blank line.