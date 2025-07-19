# -*- coding: utf-8 -*-
"""

"""
import unreal


bp_asset = unreal.EditorAssetLibrary.load_asset("/Script/Blutility.EditorUtilityToolMenuEntry'/FlipBookViewer/FlipBookViewer/FilpBookToolMenuEntry.FilpBookToolMenuEntry'")

eus = unreal.get_editor_subsystem(unreal.EditorUtilitySubsystem)


eus.try_run(bp_asset)
