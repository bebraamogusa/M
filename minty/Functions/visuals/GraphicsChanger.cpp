#include "GraphicsChanger.h"

namespace cheat {
	GraphicsChanger::GraphicsChanger() {

	}

	void GraphicsChanger::GUI() {

	}

	void GraphicsChanger::Outer() {
		if (!b_Enabled.getValue()) return;

		std::string last_lua_string = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").cameraBufferDirty = true"; // refresh da buffer
		
		//::write<float>(::read<uint64_t>(::read<uint64_t>(::read<uint64_t>(uaba + offst1) + 0x) + 0x) + 0x, f_RenderScale.getValue()); -- Render scale, requires offsets

		last_lua_string = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").outlineCorrectionWidth = " + std::to_string(f_OutlineWidth.getValue()); // Outline width

		last_lua_string = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\")._gammaValue = " + std::to_string(f_GammaScale.getValue()); // Gamma scale

		last_lua_string = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"Camera\").orthographic = " + b_OrthographicMode.getValue() ? "true" : "false"; // Orthographic mode

		switch (i_AntialiasingMode.getValue()) {
		case 0: {
				last_lua_string = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").antialiasingMode = CS.UnityEngine.Rendering.PostProcessing.PostProcessLayer.Antialiasing.None";
				break;
			}
		case 1: {
				last_lua_string = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").antialiasingMode = CS.UnityEngine.Rendering.PostProcessing.PostProcessLayer.Antialiasing.FastApproximateAntialiasing";
				break;
			}
		case 2: {
				last_lua_string = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").antialiasingMode = CS.UnityEngine.Rendering.PostProcessing.PostProcessLayer.Antialiasing.miHoYoFXAA";
				break;
			}
		case 3: {
				last_lua_string = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").antialiasingMode = CS.UnityEngine.Rendering.PostProcessing.PostProcessLayer.Antialiasing.SubpixelMorphologicalAntialiasing";
				break;
			}
		case 4: {
				last_lua_string = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").antialiasingMode = CS.UnityEngine.Rendering.PostProcessing.PostProcessLayer.Antialiasing.TemporalAntialiasing";
				break;
			}
		case 5: {
				last_lua_string = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").antialiasingMode = CS.UnityEngine.Rendering.PostProcessing.PostProcessLayer.Antialiasing.FFX_FSR_2";
				break;
			}
		}
		
		switch (i_ShadowMode.getValue()) {
		case 0: {
				app::QualitySettings_set_shadows(app::ShadowQuality::Disable);
				break;
			}
		case 1: {
				app::QualitySettings_set_shadows(app::ShadowQuality::HardOnly);
				break;
			}
		case 2: {
				app::QualitySettings_set_shadows(app::ShadowQuality::All);
				break;
			}
		case 3: {
				app::QualitySettings_set_shadows(app::ShadowQuality::ShadowsPCSS);
				break;
			}
		case 4: {
				app::QualitySettings_set_shadows(app::ShadowQuality::ShadowsPCSSHigh);
				break;
			}
		}
	}

	void GraphicsChanger::Status() {

	}
}