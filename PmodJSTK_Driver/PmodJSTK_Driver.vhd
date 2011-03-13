----------------------------------------------------------------------------------
-- Company: 
-- Engineer: Chirap Claudiu - Teodor
-- 
-- Create Date:    18:24:43 04/20/2010 
-- Design Name: 
-- Module Name:    jstkInterface - Behavioral 
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

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity jstkModule is
    Port ( CLK: in std_logic;
			  MOSI : out  STD_LOGIC;
           SS : out  STD_LOGIC;
           MISO : in  STD_LOGIC;
			  Data : out STD_LOGIC_VECTOR(22 downto 0);
           SCK : out  STD_LOGIC);
end jstkModule;

architecture Behavioral of jstkModule is

component clock1Mhz 
    Port ( clk50Mhz : in  STD_LOGIC;
           clk1Mhz : out  STD_LOGIC);
end component;

signal clk1Mhz : STD_LOGIC;
signal counter : STD_LOGIC_VECTOR(9 downto 0);
signal saveBuffer : STD_LOGIC_VECTOR(39 downto 0);
signal inputBuffer : STD_LOGIC_VECTOR(39 downto 0);


begin
			
	clkGen1Mhz : clock1Mhz port map(CLK,clk1Mhz);

	Data(9) <= saveBuffer(14);
	Data(8) <= saveBuffer(15);
	Data(7) <= saveBuffer(0);
	Data(6) <= saveBuffer(1);
	Data(5) <= saveBuffer(2);
	Data(4) <= saveBuffer(3);
	Data(3) <= saveBuffer(4);
	Data(2) <= saveBuffer(5);
	Data(1) <= saveBuffer(6);
	Data(0) <= saveBuffer(7);

	Data(19) <= saveBuffer(30);
	Data(18) <= saveBuffer(31);
	Data(17) <= saveBuffer(16);
	Data(16) <= saveBuffer(17);
	Data(15) <= saveBuffer(18);
	Data(14) <= saveBuffer(19);
	Data(13) <= saveBuffer(20);
	Data(12) <= saveBuffer(21);
	Data(11) <= saveBuffer(22);
	Data(10) <= saveBuffer(23);

	Data(20)<=saveBuffer(39);
	Data(21)<=saveBuffer(38);
	Data(22)<=saveBuffer(37);

	SCK <= clk1Mhz;

	process (clk1Mhz)
	begin
		IF (clk1Mhz'EVENT AND clk1Mhz = '1') THEN
		
--			IF (counter < 10) THEN
--				SS <= '1';
--			ELSIF (counter < 25) THEN
--				SS <= '0';
--			ELSIF (counter < 65) THEN
--				inputBuffer(conv_integer(counter)-25) <= MISO;
--			END IF;
--			
--			IF (counter<65) THEN
--				counter <= counter + 1;
--			ELSE
--				saveBuffer <= inputBuffer;
--				counter <= "0000000000";
--			END IF;
			
			IF (counter = 0) THEN
				SS <= '1';
			ELSIF (counter = 1) THEN
				ss <= '0';
			ELSIF (counter < 42) THEN
				inputBuffer(conv_integer(counter)-2) <= MISO;
			END IF;
			
			IF (counter < 42) THEN
				counter <= counter + 1;
			ELSE
				counter <= "0000000000";
				saveBuffer <= inputBuffer;
			END IF;
			
		END IF;
	end process;

end Behavioral;