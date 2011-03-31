-------------------------------------------------------------------------------
-- system_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity system_stub is
  port (
    fpga_0_clk_1_sys_clk_pin : in std_logic;
    fpga_0_rst_1_sys_rst_pin : in std_logic;
    PmodJSTK_Module_0_MOSI_pin : out std_logic;
    PmodJSTK_Module_0_SS_pin : out std_logic;
    PmodJSTK_Module_0_MISO_pin : in std_logic;
    PmodJSTK_Module_0_SCK_pin : out std_logic;
    PmodJSTK_Module_1_MOSI_pin : out std_logic;
    PmodJSTK_Module_1_SS_pin : out std_logic;
    PmodJSTK_Module_1_MISO_pin : in std_logic;
    PmodJSTK_Module_1_SCK_pin : out std_logic;
    VGA_Module_0_VSync_pin : out std_logic;
    VGA_Module_0_HSync_pin : out std_logic;
    VGA_Module_0_VGA_Blue_pin : out std_logic_vector(1 downto 0);
    VGA_Module_0_VGA_Green_pin : out std_logic_vector(2 downto 0);
    VGA_Module_0_VGA_Red_pin : out std_logic_vector(2 downto 0)
  );
end system_stub;

architecture STRUCTURE of system_stub is

  component system is
    port (
      fpga_0_clk_1_sys_clk_pin : in std_logic;
      fpga_0_rst_1_sys_rst_pin : in std_logic;
      PmodJSTK_Module_0_MOSI_pin : out std_logic;
      PmodJSTK_Module_0_SS_pin : out std_logic;
      PmodJSTK_Module_0_MISO_pin : in std_logic;
      PmodJSTK_Module_0_SCK_pin : out std_logic;
      PmodJSTK_Module_1_MOSI_pin : out std_logic;
      PmodJSTK_Module_1_SS_pin : out std_logic;
      PmodJSTK_Module_1_MISO_pin : in std_logic;
      PmodJSTK_Module_1_SCK_pin : out std_logic;
      VGA_Module_0_VSync_pin : out std_logic;
      VGA_Module_0_HSync_pin : out std_logic;
      VGA_Module_0_VGA_Blue_pin : out std_logic_vector(1 downto 0);
      VGA_Module_0_VGA_Green_pin : out std_logic_vector(2 downto 0);
      VGA_Module_0_VGA_Red_pin : out std_logic_vector(2 downto 0)
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of system : component is "user_black_box";

begin

  system_i : system
    port map (
      fpga_0_clk_1_sys_clk_pin => fpga_0_clk_1_sys_clk_pin,
      fpga_0_rst_1_sys_rst_pin => fpga_0_rst_1_sys_rst_pin,
      PmodJSTK_Module_0_MOSI_pin => PmodJSTK_Module_0_MOSI_pin,
      PmodJSTK_Module_0_SS_pin => PmodJSTK_Module_0_SS_pin,
      PmodJSTK_Module_0_MISO_pin => PmodJSTK_Module_0_MISO_pin,
      PmodJSTK_Module_0_SCK_pin => PmodJSTK_Module_0_SCK_pin,
      PmodJSTK_Module_1_MOSI_pin => PmodJSTK_Module_1_MOSI_pin,
      PmodJSTK_Module_1_SS_pin => PmodJSTK_Module_1_SS_pin,
      PmodJSTK_Module_1_MISO_pin => PmodJSTK_Module_1_MISO_pin,
      PmodJSTK_Module_1_SCK_pin => PmodJSTK_Module_1_SCK_pin,
      VGA_Module_0_VSync_pin => VGA_Module_0_VSync_pin,
      VGA_Module_0_HSync_pin => VGA_Module_0_HSync_pin,
      VGA_Module_0_VGA_Blue_pin => VGA_Module_0_VGA_Blue_pin,
      VGA_Module_0_VGA_Green_pin => VGA_Module_0_VGA_Green_pin,
      VGA_Module_0_VGA_Red_pin => VGA_Module_0_VGA_Red_pin
    );

end architecture STRUCTURE;

