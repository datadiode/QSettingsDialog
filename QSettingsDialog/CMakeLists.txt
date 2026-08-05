qt_add_library(QSettingsDialog
    core/containerelements.h
    core/exceptions.cpp core/exceptions.h
    core/qasyncsettingscontainer.cpp core/qasyncsettingscontainer.h core/qasyncsettingscontainer_p.h
    core/qsettingscontainer.cpp core/qsettingscontainer.h
    core/qsettingsdialog.cpp core/qsettingsdialog.h core/qsettingsdialog_p.h
    core/qsettingsdisplayengine.h
    core/qsettingsentry.cpp core/qsettingsentry.h core/qsettingsentry_p.h
    core/qsettingslayout.cpp core/qsettingslayout.h core/qsettingslayout_p.h
    core/qsettingsloader.cpp core/qsettingsloader.h
    core/qsettingsloaderentry.h
    core/settingspathparser.cpp core/settingspathparser.h
    core/sortedmap.h
    core/specialgroupmap.cpp core/specialgroupmap.h
    dialogui/checkinghelper.h
    dialogui/commonfactoryregistry.cpp dialogui/commonfactoryregistry.h
    dialogui/qsettingsdialogwidget.cpp dialogui/qsettingsdialogwidget.h
    dialogui/qsettingsgroupwidget.cpp dialogui/qsettingsgroupwidget.h
    dialogui/qsettingsgroupwidgetfactory.h
    dialogui/qsettingswidget.cpp dialogui/qsettingswidget.h
    dialogui/qsettingswidgetdialogengine.cpp dialogui/qsettingswidgetdialogengine.h
    dialogui/qsettingswidgetfactory.h
    dialogui/qsettingswidgetfactoryregistry.h
    dialogui/settingsdisplaydialog.cpp dialogui/settingsdisplaydialog.h dialogui/settingsdisplaydialog.ui
    dialogui/settingsengine.cpp dialogui/settingsengine.h
    loaders/qsettingspropertyentry.cpp loaders/qsettingspropertyentry.h
    loaders/qsettingspropertyloader.cpp loaders/qsettingspropertyloader.h
    loaders/qsettingssettingsloader.cpp loaders/qsettingssettingsloader.h
    qsettingsdialog_global.cpp qsettingsdialog_global.h
    qtexception.cpp qtexception.h
    submodules/DialogMaster/dialogmaster.cpp submodules/DialogMaster/dialogmaster.h
    submodules/QColorEdit/colorbutton.cpp submodules/QColorEdit/colorbutton.h
    submodules/QColorEdit/qcoloredit.cpp submodules/QColorEdit/qcoloredit.h
    submodules/QPathEdit/QPathEdit/qpathedit.cpp submodules/QPathEdit/QPathEdit/qpathedit.h
    variantwidgets/qsettingsextendedtypes.h
    variantwidgets/settingscheckbox.cpp variantwidgets/settingscheckbox.h
    variantwidgets/settingscoloredit.cpp variantwidgets/settingscoloredit.h
    variantwidgets/settingsdatetimeedit.cpp variantwidgets/settingsdatetimeedit.h
    variantwidgets/settingsenumcombobox.cpp variantwidgets/settingsenumcombobox.h
    variantwidgets/settingsenumwidgetfactory.cpp variantwidgets/settingsenumwidgetfactory.h
    variantwidgets/settingsflagschecklist.cpp variantwidgets/settingsflagschecklist.h
    variantwidgets/settingsfontcombobox.cpp variantwidgets/settingsfontcombobox.h
    variantwidgets/settingsgroupbox.cpp variantwidgets/settingsgroupbox.h
    variantwidgets/settingskeyedit.cpp variantwidgets/settingskeyedit.h
    variantwidgets/settingslineedit.cpp variantwidgets/settingslineedit.h
    variantwidgets/settingslistedit.cpp variantwidgets/settingslistedit.h variantwidgets/settingslistedit.ui
    variantwidgets/settingspathedit.cpp variantwidgets/settingspathedit.h
    variantwidgets/settingsrichtextedit.cpp variantwidgets/settingsrichtextedit.h
    variantwidgets/settingsslider.cpp variantwidgets/settingsslider.h
    variantwidgets/settingsspinbox.cpp variantwidgets/settingsspinbox.h
    variantwidgets/variantwidgetsregistrator.cpp variantwidgets/variantwidgetsregistrator.h
)

set_target_properties(QSettingsDialog PROPERTIES
    AUTOMOC ON
    AUTORCC ON
)

target_include_directories(QSettingsDialog PUBLIC
    core
    dialogui
    loaders
    submodules/DialogMaster
    submodules/QColorEdit
    submodules/QPathEdit/QPathEdit
    variantwidgets
)

target_compile_definitions(QSettingsDialog PRIVATE
    QSETTINGSDIALOG_LIBRARY
)

target_link_libraries(QSettingsDialog PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)


# Resources:
set_source_files_properties("resources/gear_in.ico"
    PROPERTIES QT_RESOURCE_ALIAS "gearSettings.ico"
)
set_source_files_properties("resources/setting_tools.ico"
    PROPERTIES QT_RESOURCE_ALIAS "settings.ico"
)
set(qsettingsdialog_res_resource_files
    "resources/gear_in.ico"
    "resources/setting_tools.ico"
)

qt_add_resources(QSettingsDialog "qsettingsdialog_res"
    PREFIX
        "/QSettingsDialog/icons"
    FILES
        ${qsettingsdialog_res_resource_files}
)
set_source_files_properties("submodules/QPathEdit/QPathEdit/Fatcow-Farm-Fresh-Dialog.ico"
    PROPERTIES QT_RESOURCE_ALIAS "dialog.ico"
)
set(qpathedit_res_resource_files
    "submodules/QPathEdit/QPathEdit/Fatcow-Farm-Fresh-Dialog.ico"
)

qt_add_resources(QSettingsDialog "qpathedit_res"
    PREFIX
        "/qpathedit/icons"
    BASE
        "submodules/QPathEdit/QPathEdit"
    FILES
        ${qpathedit_res_resource_files}
)
set_source_files_properties("variantwidgets/resources/add.ico"
    PROPERTIES QT_RESOURCE_ALIAS "add.ico"
)
set_source_files_properties("variantwidgets/resources/arrow_down.ico"
    PROPERTIES QT_RESOURCE_ALIAS "down.ico"
)
set_source_files_properties("variantwidgets/resources/arrow_up.ico"
    PROPERTIES QT_RESOURCE_ALIAS "up.ico"
)
set_source_files_properties("variantwidgets/resources/calculator.ico"
    PROPERTIES QT_RESOURCE_ALIAS "calc.ico"
)
set_source_files_properties("variantwidgets/resources/delete.ico"
    PROPERTIES QT_RESOURCE_ALIAS "delete.ico"
)
set_source_files_properties("variantwidgets/resources/outlook_calendar_day.ico"
    PROPERTIES QT_RESOURCE_ALIAS "today.ico"
)
set(qsettingsdialog_variantwidgets_res_resource_files
    "variantwidgets/resources/add.ico"
    "variantwidgets/resources/arrow_down.ico"
    "variantwidgets/resources/arrow_up.ico"
    "variantwidgets/resources/calculator.ico"
    "variantwidgets/resources/delete.ico"
    "variantwidgets/resources/outlook_calendar_day.ico"
)

qt_add_resources(QSettingsDialog "qsettingsdialog_variantwidgets_res"
    PREFIX
        "/QSettingsDialog/icons"
    BASE
        "variantwidgets"
    FILES
        ${qsettingsdialog_variantwidgets_res_resource_files}
)

install(TARGETS QSettingsDialog
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
