function Component()
{
    component.loaded.connect(this, Component.prototype.loaded);
    installer.installationFinished.connect(this, Component.prototype.installationFinishedPageIsShown);
    installer.finishButtonClicked.connect(this, Component.prototype.installationFinished);
}

Component.prototype.loaded = function()
{
    try {
        if (installer.value("os") == "win" && installer.isInstaller())
            installer.addWizardPageItem(component, "AssociateCommonFiletypesForm", QInstaller.TargetDirectory);
    } catch(e) {
        print(e);
    }
}

Component.prototype.beginInstallation = function()
{
    component.qtdbfBinaryPath = installer.value("TargetDir");
    if (installer.value("os") == "win") {
        component.qtdbfBinaryPath = component.qtdbfBinaryPath + "\\qtdbf.exe";
        component.qtdbfBinaryPath = component.qtdbfBinaryPath.replace(/\//g, "\\");
    }
}

registerWindowsFileTypeExtensions = function()
{
    var dbfExtensions = new Array("dbf");

    for (var i = 0; i < headerExtensions.length; ++i) {
        component.addOperation( "RegisterFileType",
                                "dbf",
                                component.qtdbfBinaryPath + " '%1'",
                                "DBF file",
                                "text/plain",
                                component.qtdbfBinaryPath + ",3",
                                "ProgId=qtdbf.dbf");
    }
}
Component.prototype.createOperations = function()
{
    component.createOperations();
    if ( installer.value("os") == "win" )
    {
        component.addOperation( "CreateShortcut",
                                component.qtdbfBinaryPath,
                                "@StartMenuDir@/qtdbf.lnk",
                                "workingDirectory=@homeDir@" );
        try {
            if (component.userInterface("AssociateCommonFiletypesForm").AssociateCommonFiletypesCheckBox
                .checked) {
                    registerWindowsFileTypeExtensions();
            }
        } catch(e) {
            print(e);
        }
    }
}

Component.prototype.installationFinishedPageIsShown = function()
{
    try {
        if (component.installed && installer.isInstaller() && installer.status == QInstaller.Success) {
            installer.addWizardPageItem( component, "LaunchQtDBFCheckBoxForm", QInstaller.InstallationFinished );
        }
    } catch(e) {
        print(e);
    }
}

Component.prototype.installationFinished = function()
{
    try {
        if (component.installed && installer.isInstaller() && installer.status == QInstaller.Success) {
            var isLaunchQtDBFCheckBoxChecked = component.userInterface("LaunchQtDBFCheckBoxForm").launchQtDBFCheckBox.checked;
            if (isLaunchQtDBFCheckBoxChecked)
                installer.executeDetached(component.qtdbfBinaryPath, new Array(), "@homeDir@");
        }
    } catch(e) {
        print(e);
    }
}

