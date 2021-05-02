/* -*- C++ -*- */
#pragma once

namespace Menu {
  template<typename Dev,Dev& dev>
  struct SerialOut {
    template<typename O>
    struct Part:O {
      void write(const char* o,Idx len){dev.write(o,len);}
      template<typename Data>
      void print(Data o) {dev.print(o);}
      void nl() {dev.println();}
    };
  };

};//Menu namespace
