----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:32:43 03/11/2011 
-- Design Name: 
-- Module Name:    top - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity top is
		Port ( clk50Mhz : in  STD_LOGIC;
				Led : out STD_LOGIC_VECTOR(0 to 7);
				SS : out STD_LOGIC;
				MOSI : out STD_LOGIC;
				MISO : in STD_LOGIC;
				SCK : out STD_LOGIC;
				sw : in STD_LOGIC_VECTOR(0 to 7)
				);
end top;

architecture Behavioral of top is

component jstkModule 
    Port ( CLK: in std_logic;
			  MOSI : out  STD_LOGIC;
           SS : out  STD_LOGIC;
           MISO : in  STD_LOGIC;
           SCK : out  STD_LOGIC;
			  Data : out STD_LOGIC_VECTOR(22 downto 0));
end component;

signal LEDs : STD_LOGIC_VECTOR(0 to 2);
signal jstkData : STD_LOGIC_VECTOR(22 downto 0);
signal SS_Signal : STD_LOGIC;
signal MOSI_Signal : STD_LOGIC;
signal MISO_Signal : STD_LOGIC;
signal SCK_Signal : STD_LOGIC;
signal clk_Signal : STD_LOGIC; 

begin
SS <= SS_Signal;
MOSI <= MOSI_Signal;
MISO_Signal <= MISO;
SCK <= SCK_Signal;
clk_Signal <= clk50Mhz;
jstk : jstkModule port map (clk_Signal,MOSI_Signal,SS_Signal,MISO_Signal,SCK_Signal,jstkData);


process (clk50Mhz)
begin
IF (sw(7) = '1') THEN
Led(0 to 7) <= jstkData(7 downto 0);
ELSIF (sw(6) = '1') THEN
Led(0 to 5) <= "000000";
Led(6 to 7) <= jstkData(9 downto 8);
ELSIF (sw(5) = '1') THEN
Led(0 to 7) <= jstkData(17 downto 10);
ELSIF (sw(4) = '1') THEN
Led(0 to 5) <= "000000";
Led(6 to 7) <= jstkData(19 downto 18);
ELSIF (sw(3) = '1') THEN
Led(0 to 4) <= "00000";
Led(5 to 7) <= jstkData(22 downto 20);
ELSE
Led <= "00000001";
END IF;

end process;

end Behavioral;

