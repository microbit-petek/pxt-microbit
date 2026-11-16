#include "pxt.h"

namespace music {
    /**
     * Internal use only
     **/
    //% async
    void __playSoundExpression(String nodes, bool waitTillDone) {
      // TODO
      #ifndef NRF54L_SERIES
#if MICROBIT_CODAL
        if (waitTillDone)
            uBit.audio.soundExpressions.play(MSTR(nodes));
        else
            uBit.audio.soundExpressions.playAsync(MSTR(nodes));
#else
        target_panic(PANIC_VARIANT_NOT_SUPPORTED);
#endif
      #endif // NRF54L_SERIES
    }

    /**
    * Internal use only
    */
    //% 
    void __stopSoundExpressions() {
      // TODO
      #ifndef NRF54L_SERIES
#if MICROBIT_CODAL
        uBit.audio.soundExpressions.stop();
#endif
      #endif // NRF54L_SERIES
    }
}
