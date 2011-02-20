----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:25:23 02/19/2011 
-- Design Name: 
-- Module Name:    clk25MHz - Behavioral 
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

entity clk25MHz is
    Port ( clk : in  STD_LOGIC;
           sclk : out  STD_LOGIC);
end clk25MHz;

architecture Behavioral of clk25MHz is


signal slow_clk: STD_LOGIC;

begin

	process(clk)
	variable count : Integer := 0;
	begin
		if rising_edge(clk) then
			if (count = 1) then
				slow_clk <= not slow_clk;
				count := 0;
			else
				count := count + 1;
			end if;
		end if;
	end process;
	
	sclk <= slow_clk;
	
end Behavioral;

