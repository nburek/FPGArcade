-------------------------------------------------------------------------------
-- vga_driver_wrapper.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library top_v1_00_a;
use top_v1_00_a.all;

entity vga_driver_wrapper is
  port (
    VGA_Red : out std_logic_vector(2 downto 0);
    VGA_Green : out std_logic_vector(2 downto 0);
    VGA_Blue : out std_logic_vector(1 downto 0);
    HSync : out std_logic;
    VSync : out std_logic;
    clk : in std_logic;
    BlockPosition : in std_logic_vector(0 to 18);
    PaddlePosition : in std_logic_vector(0 to 17)
  );
end vga_driver_wrapper;

architecture STRUCTURE of vga_driver_wrapper is

  component top is
    port (
      VGA_Red : out std_logic_vector(2 downto 0);
      VGA_Green : out std_logic_vector(2 downto 0);
      VGA_Blue : out std_logic_vector(1 downto 0);
      HSync : out std_logic;
      VSync : out std_logic;
      clk : in std_logic;
      BlockPosition : in std_logic_vector(0 to 18);
      PaddlePosition : in std_logic_vector(0 to 17)
    );
  end component;

begin

  VGA_Driver : top
    port map (
      VGA_Red => VGA_Red,
      VGA_Green => VGA_Green,
      VGA_Blue => VGA_Blue,
      HSync => HSync,
      VSync => VSync,
      clk => clk,
      BlockPosition => BlockPosition,
      PaddlePosition => PaddlePosition
    );

end architecture STRUCTURE;

