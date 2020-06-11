function Component()
{
 
}

Component.prototype.createOperations = function()
{
    component.createOperations();
    component.addElevatedOperation("Execute", "@TargetDir@/AService.exe", "install", "UNDOEXECUTE", "@TargetDir@/AService.exe", "uninstall");
    component.addElevatedOperation("CreateShortcut", "@TargetDir@/GUIAService.exe", "@DesktopDir@/Курсовой антивирус.lnk");
}