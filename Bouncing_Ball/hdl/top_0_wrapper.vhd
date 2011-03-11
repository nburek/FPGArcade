-------------------------------------------------------------------------------
-- top_0_wrapper.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library top_v1_00_a;
use top_v1_00_a.all;

entity top_0_wrapper is
  port (
    VGA_Red : out std_logic_vector(2 downto 0);
    VGA_Green : out std_logic_vector(2 downto 0);
    VGA_Blue : out std_logic_vector(1 downto 0);
    HSync : out std_logic;
    VSync : out std_logic;
    clk : in std_logic;
    BlockPosition : in std_logic_vector(0 to 19)
  );
end top_0_wrapper;

architecture STRUCTURE of top_0_wrapper is

  component top is
    port (
      VGA_Red : out std_logic_vector(2 downto 0);
      VGA_Green : out std_logic_vector(2 downto 0);
      VGA_Blue : out std_logic_vector(1 downto 0);
      HSync : out std_logic;
      VSync : out std_logic;
      clk : in std_logic;
      BlockPosition : in std_logic_vector(0 to 19)
    );
  end component;

begin

  top_0 : top
    port map (
      VGA_Red => VGA_Red,
      VGA_Green => VGA_Green,
      VGA_Blue => VGA_Blue,
      HSync => HSync,
      VSync => VSync,
      clk => clk,
      BlockPosition => BlockPosition
    );

end architecture STRUCTURE;

