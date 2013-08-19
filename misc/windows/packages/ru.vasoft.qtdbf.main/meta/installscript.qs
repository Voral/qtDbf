function Component()
{
     var programFiles = installer.environmentVariable("ProgramFiles");
     if (programFiles != "")
         installer.setValue("TargetDir", programFiles + "/qtdbf");
}
Component.prototype.isDefault = function()
{
     return true;
}
Component.prototype.createOperations = function()
 {
     try {
         // call the base create operations function
         component.createOperations();
     } catch (e) {
         print(e);
     }
 }
