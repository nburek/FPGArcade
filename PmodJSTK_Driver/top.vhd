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
				SCK : out STD_LOGIC
				);
end top;

architecture Behavioral of top is

component PmodJSTK_Driver
    Port ( clk50Mhz : in  STD_LOGIC;
           LED : in  STD_LOGIC_VECTOR(0 to 2);
           Data : out  STD_LOGIC_VECTOR(0 to 22);
			  SS : out STD_LOGIC;
			  MOSI : out STD_LOGIC;
			  MISO : in STD_LOGIC;
			  SCK : out STD_LOGIC);
end component;

signal LEDs : STD_LOGIC_VECTOR(0 to 2);
signal jstkData : STD_LOGIC_VECTOR(0 to 22);
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

jstk : PmodJSTK_Driver port map(clk_Signal,LEDs,jstkData,SS_Signal,MOSI_Signal,MISO_Signal,SCK_Signal);

Led <= jstkData(0 to 7);

end Behavioral;

