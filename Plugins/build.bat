Rem call "F:\Epic Games\Unreal Engines\UE_4.25\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -TargetPlatform=Win64 -Plugin="C:\Users\Matthew\Documents\Unreal Projects\quadditch-unreal\plugin-src\ROSIntegration\ROSIntegration.uplugin" -Platform=Win64 -Package="C:\Users\Matthew\Documents\Unreal Projects\quadditch-unreal\Plugins\ROSIntegration\" -Rocket

CALL "C:\Program Files\Epic Games\UE_4.25\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -TargetPlatform=Win64 -Plugin="%~dp0/ROSIntegration/ROSIntegration.uplugin" -Platform=Win64 -Package="%~dp0/ROSIntegrationBuilt/" -Rocket
RMDIR /S /Q "%~dp0ROSIntegration\Binaries", "%~dp0ROSIntegration\Intermediate"
MOVE /Y "%~dp0ROSIntegrationBuilt\Binaries" "%~dp0ROSIntegration\Binaries"
MOVE /Y "%~dp0ROSIntegrationBuilt\Intermediate" "%~dp0ROSIntegration\Intermediate"
RMDIR /S /Q "%~dp0ROSIntegrationBuilt"