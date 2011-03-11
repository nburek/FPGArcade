----------------------------------------------------------------------------------
-- Company: Loras College
-- Engineer: Nick Burek
-- 
-- Create Date:    12:25:23 02/19/2011 
-- Design Name: 
-- Module Name:    clk25MHz - Behavioral 
-- Project Name: VGA_Driver
-- Target Devices: Nexys2
-- Tool versions: 
-- Description: This module reduces a 50Mhz clock signal to a 25Mhz clock signal.
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

entity clk25MHz is
    Port ( clk : in  STD_LOGIC;
           sclk : out  STD_LOGIC);
end clk25MHz;

architecture Behavioral of clk25MHz is


signal slow_clk: STD_LOGIC;

begin

	process(clk)
	
	begin
		IF (clk'EVENT and clk = '1') THEN  -- On rising edge of clock signal
		
			slow_clk <= not slow_clk; -- toggle the slow clock
			
		END IF;
		
	end process;
	
	sclk <= slow_clk;
	
end Behavioral;

