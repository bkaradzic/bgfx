#ifndef SWIFT_ADAPTER_H_HEADER_GUARD
#define SWIFT_ADAPTER_H_HEADER_GUARD

#include <CompositorServices/CompositorServices.h>

class BgfxAdapter {
private:
  bool m_initialized = false;
  cp_layer_renderer_t m_layerRenderer = NULL;
  void render(void);

public:
  BgfxAdapter(cp_layer_renderer_t layerRenderer) : m_layerRenderer(layerRenderer) {
  }
  
  ~BgfxAdapter() {
    shutdown();
  }
  
  bool initialize(void);
  void shutdown(void);
  void renderLoop(void);
};

#endif
