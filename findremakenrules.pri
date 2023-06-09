# Author(s) : Loic Touraine, Stephane Leduc

win32 {
    USERHOMEFOLDER = $$clean_path($$(USERPROFILE))
    isEmpty(USERHOMEFOLDER) {
        USERHOMEFOLDER = $$clean_path($$(HOMEDRIVE)$$(HOMEPATH))
    }
}

exists(builddefs/qmake) {
    QMAKE_REMAKEN_RULES_ROOT=builddefs/qmake
}
else {
    QMAKE_REMAKEN_RULES_ROOT = $$clean_path($$(REMAKEN_RULES_ROOT))
    !isEmpty(QMAKE_REMAKEN_RULES_ROOT) {
        QMAKE_REMAKEN_RULES_ROOT = $$clean_path($$(REMAKEN_RULES_ROOT)/qmake)
    }
    else {
        QMAKE_REMAKEN_RULES_ROOT=$${USERHOMEFOLDER}/.remaken/rules/qmake
    }
}

!exists($${QMAKE_REMAKEN_RULES_ROOT}) {
    error("Unable to locate remaken rules in " $${QMAKE_REMAKEN_RULES_ROOT} ". Either check your remaken installation, or provide the path to your remaken qmake root folder rules in REMAKEN_RULES_ROOT environment variable.")
}

message("Remaken qmake build rules used : " $$QMAKE_REMAKEN_RULES_ROOT)