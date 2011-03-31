-------------------------------------------------------------------------------
-- pmodjstk_module_0_wrapper.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library PmodJSTK_Module_v1_00_a;
use PmodJSTK_Module_v1_00_a.all;

entity pmodjstk_module_0_wrapper is
  port (
    CLK : in std_logic;
    MOSI : out std_logic;
    SS : out std_logic;
    MISO : in std_logic;
    Data : out std_logic_vector(22 downto 0);
    SCK : out std_logic
  );
end pmodjstk_module_0_wrapper;

architecture STRUCTURE of pmodjstk_module_0_wrapper is

  component pmodjstk_module is
    port (
      CLK : in std_logic;
      MOSI : out std_logic;
      SS : out std_logic;
      MISO : in std_logic;
      Data : out std_logic_vector(22 downto 0);
      SCK : out std_logic
    );
  end component;

begin

  PmodJSTK_Module_0 : pmodjstk_module
    port map (
      CLK => CLK,
      MOSI => MOSI,
      SS => SS,
      MISO => MISO,
      Data => Data,
      SCK => SCK
    );

end architecture STRUCTURE;

