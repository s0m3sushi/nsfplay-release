#ifndef _NES_VRC6_H_
#define _NES_VRC6_H_
#include "../device.h"

namespace xgm
{

  class NES_VRC6:public ISoundChip
  {
  public:
    enum
    {
      OPT_END
    };
  protected:
    UINT32 counter[3]; // frequency divider
	UINT64 saw_counter;
	UINT64 saw_max_counter;
    UINT32 phase[3];   // phase counter
    UINT32 freq2[3];   // adjusted frequency
    int count14;       // saw 14-stage counter

    //int option[OPT_END];
    int mask;
    INT32 sm[2][3]; // stereo mix
    int duty[2];
    int volume[3];
    int enable[3];
    int gate[3];
    UINT32 freq[3];
    double calc_sqr (int i, UINT32 clocks);
    double calc_saw (UINT32 clocks);
    bool halt;
    int freq_shift;
    double clock, rate;
    double out[3];
    TrackInfoBasic trkinfo[3];

	double linear_approximate(double now_a, double min_a, double max_a, double min_b, double max_b);
	void update_saw_counter();
  public:
      NES_VRC6 ();
     ~NES_VRC6 ();

    virtual void Reset ();
    virtual void Tick (UINT32 clocks);
    virtual UINT32 Render (INT32 b[2]);
    virtual bool Read (UINT32 adr, UINT32 & val, UINT32 id=0);
    virtual bool Write (UINT32 adr, UINT32 val, UINT32 id=0);
    virtual void SetClock (double);
    virtual void SetRate (double);
    virtual void SetOption (int, int);
    virtual void SetMask (int m){ mask = m; }
    virtual void SetStereoMix (int trk, xgm::INT16 mixl, xgm::INT16 mixr);
    virtual ITrackInfo *GetTrackInfo(int trk);
  };

}                               // namespace

#endif
