{{#LOADTYPE1_SECTION}}
ModPowerSystems.PhasorSinglePhase.Households.HouseholdType1 {{NAME}}(Household_Vnom = {{HOUSEHOLD_VNOM}}, Load_Type = {{LOAD_TYPE}})
{{/LOADTYPE1_SECTION}}
{{#LOADTYPE2_SECTION}}
ModPowerSystems.PhasorSinglePhase.Households.HouseholdType1 {{NAME}}(Household_Vnom = {{HOUSEHOLD_VNOM}}, Load_Pnom = {{LOAD_PNOM}}, Load_Qnom = {{LOAD_QNOM}}, Load_ProfileFileName = "{{LOAD_PROFILE_FILENAME}}", Load_ProfileName = "{{LOAD_PROFILE_NAME}}", Load_Type = {{LOAD_TYPE}})
{{/LOADTYPE2_SECTION}}
{{#LOADTYPE3_SECTION}}
ModPowerSystems.PhasorSinglePhase.Households.HouseholdType1 {{NAME}}(Household_Vnom = {{HOUSEHOLD_VNOM}}, Load_ProfileFileName = "{{LOAD_PROFILE_FILENAME}}", Load_ProfileName = "{{LOAD_PROFILE_NAME}}", Load_Type = {{LOAD_TYPE}})
{{/LOADTYPE3_SECTION}}
annotation (Placement(visible = {{VISIBLE}}, transformation(extent = {{TRANS_EXTENT_POINTS}}, rotation = {{ROTATION}}, origin = {{ORIGIN_POINT}})));
