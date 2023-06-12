#ifndef ext_module_h
#define ext_module_h

class modules{
  public:
  modules();
  
  void EEPROM_WRITE(int deviceaddress,unsigned int eeaddress,byte data); // done
  int EEPROM_GET(int address,unsigned int eeaddress); // done

  void DISPLAY_SET_TEXT(int text); // done
};

extern modules MODULE;
#endif
