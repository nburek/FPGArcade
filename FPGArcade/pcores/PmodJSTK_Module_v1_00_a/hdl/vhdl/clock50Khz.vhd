----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:33:25 03/11/2011 
-- Design Name: 
-- Module Name:    clock50Khz - Behavioral 
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
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity clock50Khz is
    Port ( clk50Mhz : in  STD_LOGIC;
           clk50Khz : out  STD_LOGIC);
end clock50Khz;

architecture Behavioral of clock50Khz is

signal count : STD_LOGIC_VECTOR(9 downto 0) := "0000000000";

begin
	clk50Khz <= count(9); -- overflow resets this from 1 to 0 when adding unsigned
	
	process (clk50Mhz)
	begin
		IF (clk50Mhz'EVENT AND clk50Mhz='1') THEN
			count <= count + 1; 
		END IF;
	end process;


end Behavioral;

