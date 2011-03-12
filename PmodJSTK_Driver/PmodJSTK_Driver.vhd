----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:54:57 03/11/2011 
-- Design Name: 
-- Module Name:    PmodJSTK_Driver - Behavioral 
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
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity PmodJSTK_Driver is
    Port ( clk50Mhz : in  STD_LOGIC;
           LED : in  STD_LOGIC_VECTOR(0 to 2);
           Data : out  STD_LOGIC_VECTOR(0 to 22);
			  SS : out STD_LOGIC;
			  MOSI : out STD_LOGIC;
			  MISO : in STD_LOGIC;
			  SCK : out STD_LOGIC);
end PmodJSTK_Driver;

architecture Behavioral of PmodJSTK_Driver is

signal counter : STD_LOGIC_VECTOR(0 to 6);
signal clk1Mhz : STD_LOGIC;
signal bufferSignal : STD_LOGIC_VECTOR(0 to 9);

component clock1Mhz
	Port (clk50Mhz : in STD_LOGIC;
			clk1Mhz : out STD_LOGIC);
end component;


begin

clkGen1Mhz: clock1Mhz port map (clk50Mhz,clk1Mhz);

SCK <= clk1Mhz;

process (clk1Mhz)
begin
	IF (clk1Mhz'EVENT AND clk1Mhz='1') THEN
		IF (counter = 0) THEN
			SS <= '1'; -- turns it off since it's active low
		ELSIF (counter = 10) THEN
			SS <= '0'; -- turns it on since it's active low
		ELSIF (counter >= 25 AND counter < 33) THEN
			bufferSignal(32-counter) <= MISO;
		ELSIF (counter >=39 AND counter < 41) THEN --33 through 38 can be ignored since they're junk, 39 and 40 are the upper bits
			bufferSignal(48-counter) <= MISO;
		END IF;
		counter <= counter + 1;
	END IF;

end process;

end Behavioral;

