#ifndef server_h
#define server_h

#define APSSID "ANONYMOUS"
#define APPSK  "11235813"

class serverClas{
  public:
  serverClas();
  void SETUP();
  void LISTEN();
  void ANIMATE();
};

extern serverClas SERVER;
#endif
