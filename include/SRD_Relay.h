#ifndef SRD_RELAY_H
#define SRD_RELAY_H

#define ON_STATE 1
#define OFF_STATE 0

/// This is the SRD_Relay class
///
/// This class allows the board to control any 5v relient relay modules such as zelt etc.
class SRD_Relay_class
{
    public:
        void SRD_Relay_Init();
        void SRD_Relay_ON();
        void SRD_Relay_OFF();

    private:
};


#endif