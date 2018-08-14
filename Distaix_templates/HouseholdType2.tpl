{{#LOADTYPE1_SECTION}}
ModPowerSystems.PhasorSinglePhase.Households.HouseholdType2 {{NAME}}(Household_Vnom = {{HOUSEHOLD_VNOM}}, Load_Type = {{LOAD_TYPE}}, PV_Controller = {{PV_CONTROLLER}}, PV_CurtailmentLimit = {{PV_CURTAILMENT_LIMIT}}, PV_Pnom = {{PV_PNOM}}, PV_ProfileFileName = "{{PV_PROFILE_FILENAME}}", PV_ProfileName = "{{PV_PROFILE_NAME}}", PV_SystemOn = {{PV_SYSTEMON}})
{{/LOADTYPE1_SECTION}}
{{#LOADTYPE2_SECTION}}
ModPowerSystems.PhasorSinglePhase.Households.HouseholdType2 {{NAME}}(Household_Vnom = {{HOUSEHOLD_VNOM}}, Load_Pnom = {{LOAD_PNOM}}, Load_Qnom = {{LOAD_QNOM}}, Load_Type = {{LOAD_TYPE}}, Load_ProfileFileName = "{{LOAD_PROFILE_FILENAME}}", Load_ProfileName = "{{LOAD_PROFILE_NAME}}",
PV_Controller = {{PV_CONTROLLER}}, PV_CurtailmentLimit = {{PV_CURTAILMENT_LIMIT}}, PV_Pnom = {{PV_PNOM}}, PV_ProfileFileName = "{{PV_PROFILE_FILENAME}}", PV_ProfileName = "{{PV_PROFILE_NAME}}", PV_SystemOn = {{PV_SYSTEMON}})
{{/LOADTYPE2_SECTION}}
{{#LOADTYPE3_SECTION}}
ModPowerSystems.PhasorSinglePhase.Households.HouseholdType2 {{NAME}}(Household_Vnom = {{HOUSEHOLD_VNOM}}, Load_Type = {{LOAD_TYPE}}, Load_ProfileFileName = "{{LOAD_PROFILE_FILENAME}}", Load_ProfileName = "{{LOAD_PROFILE_NAME}}",
PV_Controller = {{PV_CONTROLLER}}, PV_CurtailmentLimit = {{PV_CURTAILMENT_LIMIT}}, PV_Pnom = {{PV_PNOM}}, PV_ProfileFileName = "{{PV_PROFILE_FILENAME}}", PV_ProfileName = "{{PV_PROFILE_NAME}}", PV_SystemOn = {{PV_SYSTEMON}})
{{/LOADTYPE3_SECTION}}
annotation (Placement(visible = {{VISIBLE}}, transformation(extent = {{TRANS_EXTENT_POINTS}}, rotation = {{ROTATION}}, origin = {{ORIGIN_POINT}})));