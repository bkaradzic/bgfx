import SwiftUI
import CompositorServices

// Default configuration
struct ContentStageConfiguration: CompositorLayerConfiguration {
  func makeConfiguration(capabilities: LayerRenderer.Capabilities, configuration: inout LayerRenderer.Configuration) {
    configuration.depthFormat = .depth32Float
    configuration.colorFormat = .bgra8Unorm_srgb

    let foveationEnabled = capabilities.supportsFoveation
    configuration.isFoveationEnabled = foveationEnabled

    let options: LayerRenderer.Capabilities.SupportedLayoutsOptions = foveationEnabled ? [.foveationEnabled] : []
    let supportedLayouts = capabilities.supportedLayouts(options: options)

    configuration.layout = supportedLayouts.contains(.layered) ? .layered : .dedicated
  }
}

@main
struct ExampleApp: App {
	var body: some Scene {
		ImmersiveSpace {
			CompositorLayer(configuration: ContentStageConfiguration()) { layerRenderer in
				let renderThread = Thread {
					var engine = BgfxAdapter(layerRenderer)
					engine.renderLoop()
				}
				renderThread.name = "Render Thread"
				renderThread.start()
			}
		}
	}
}
