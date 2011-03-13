----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:33:25 03/11/2011 
-- Design Name: 
-- Module Name:    clock1Mhz - Behavioral 
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

entity clock1Mhz is
    Port ( clk50Mhz : in  STD_LOGIC;
           clk1Mhz : out  STD_LOGIC);
end clock1Mhz;

architecture Behavioral of clock1Mhz is

signal slow_clk: STD_LOGIC;
signal count : STD_LOGIC_VECTOR(9 downto 0) := "0000000000";

begin
	clk1Mhz <= count(9);
	process (clk50Mhz)
	begin
		IF (clk50Mhz'EVENT AND clk50Mhz='1') THEN
--			IF (count = "11001") THEN -- if count = 25
--				count <= "000000";
--				slow_clk <= not slow_clk;
--			ELSE
--				count <= count + 1;
--			END IF;
count <= count + 1;
		END IF;
	end process;

	--clk1Mhz <= slow_clk;

end Behavioral;

