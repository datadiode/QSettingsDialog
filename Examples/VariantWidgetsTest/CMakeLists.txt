qt_add_executable(VariantWidgetsTest WIN32 MACOSX_BUNDLE
    main.cpp
    metawrapper.cpp metawrapper.h
)
target_include_directories(VariantWidgetsTest PRIVATE
    .././../QSettingsDialog
    .././../QSettingsDialog/core
    .././../QSettingsDialog/dialogui
    .././../QSettingsDialog/loaders
    .././../QSettingsDialog/variantwidgets
)

target_link_libraries(VariantWidgetsTest PRIVATE
    Qt::Core
    Qt::Gui
	Qt::Widgets
)

target_link_directories(VariantWidgetsTest PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}/.././../../QSettingsDialog/$<CONFIG>
)

target_link_libraries(VariantWidgetsTest PRIVATE
	QSettingsDialog
)

install(TARGETS VariantWidgetsTest
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET VariantWidgetsTest
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
