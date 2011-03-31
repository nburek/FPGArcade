-------------------------------------------------------------------------------
-- vga_module_0_wrapper.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library VGA_Module_v1_00_a;
use VGA_Module_v1_00_a.all;

entity vga_module_0_wrapper is
  port (
    VGA_Red : out std_logic_vector(2 downto 0);
    VGA_Green : out std_logic_vector(2 downto 0);
    VGA_Blue : out std_logic_vector(1 downto 0);
    HSync : out std_logic;
    VSync : out std_logic;
    clk50Mhz : in std_logic;
    graphicsInstruction : in std_logic_vector(31 downto 0);
    instructionClk : in std_logic
  );
end vga_module_0_wrapper;

architecture STRUCTURE of vga_module_0_wrapper is

  component vga_module is
    port (
      VGA_Red : out std_logic_vector(2 downto 0);
      VGA_Green : out std_logic_vector(2 downto 0);
      VGA_Blue : out std_logic_vector(1 downto 0);
      HSync : out std_logic;
      VSync : out std_logic;
      clk50Mhz : in std_logic;
      graphicsInstruction : in std_logic_vector(31 downto 0);
      instructionClk : in std_logic
    );
  end component;

begin

  VGA_Module_0 : vga_module
    port map (
      VGA_Red => VGA_Red,
      VGA_Green => VGA_Green,
      VGA_Blue => VGA_Blue,
      HSync => HSync,
      VSync => VSync,
      clk50Mhz => clk50Mhz,
      graphicsInstruction => graphicsInstruction,
      instructionClk => instructionClk
    );

end architecture STRUCTURE;

