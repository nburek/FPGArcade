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

signal bitCounter : STD_LOGIC_VECTOR(3 downto 0) := "0000";
signal byteCounter : STD_LOGIC_VECTOR(3 downto 0):= "0000";
signal clk1Mhz : STD_LOGIC;
signal bufferSignal : STD_LOGIC_VECTOR(0 to 9):= "0000000000";
signal betweenBytes : STD_LOGIC := '0';

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
		
		IF (byteCounter = 0) THEN
			Data(0) <= '1';
			IF (bitCounter < 10) THEN
				SS <= '1'; --inactive high
			ELSIF (bitCounter < 25) THEN
				SS <= '0'; --active low
			END IF;
			bitCounter <= bitCounter + 1;
			
			IF (bitCounter = 25) THEN
				bitCounter <= "0000";
				byteCounter <= byteCounter + 1;
			END IF;
		
		ELSIF (betweenBytes = '1') THEN -- if you need to wait between bytes
		Data(1) <= '1';
			IF (bitCounter<10) THEN
				bitCounter <= bitCounter + 1;
			ELSE
				bitCounter <= "0000";
				betweenBytes <= '0';
			END IF;
		
		ELSIF (byteCounter = 1 OR byteCounter = 3) THEN
		Data(2) <= '1';
			bufferSignal(conv_integer(7-bitCounter)) <= MISO;
			bitCounter <= bitCounter + 1;
			
			IF (bitCounter = 8) THEN
				bitCounter <= "0000";
				betweenBytes <= '1';
				byteCounter <= byteCounter + 1;
			END IF;
		ELSIF (byteCounter = 2 OR byteCounter = 4) THEN
		Data(3) <= '1';
			IF (bitCounter = 6) THEN
				bufferSignal(9) <= MISO;
			ELSIF (bitCounter = 8) THEN
				bufferSignal(8) <= MISO;
			END IF;
			
			bitCounter <= bitCounter + 1;
			
			IF (bitCounter = 8) THEN
				IF (byteCounter = 2) THEN
--					Data(0 to 9) <= bufferSignal(0 to 9);
					--Data(0 to 9) <= "1010101010";
				ELSIF (byteCounter = 4) THEN
					Data(10 to 19) <= bufferSignal(0 to 9);
					--Data(0 to 9) <= "0101010101";
				END IF;
				bitCounter <= "0000";
				betweenBytes <= '1';
				byteCounter <= byteCounter + 1;
			END IF;
		ELSIF (byteCounter = 5) THEN
		Data(4) <= '1';
			IF (bitCounter = 5) THEN
				Data(20) <= MISO;
			ELSIF (bitCounter = 6) THEN
				Data(21) <= MISO;
			ELSIF (bitCounter = 7) THEN
				Data(22) <= MISO;
			END IF;
			
			bitCounter <= bitCounter + 1;
			
			IF (bitCounter = 8) THEN
				bitCounter <= "0000";
				byteCounter <= "0000";
			END IF;
		END IF;
			
		
		
	END IF;

end process;

end Behavioral;

