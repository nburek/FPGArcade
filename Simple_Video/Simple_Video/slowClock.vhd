library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity slowClock is
    Port ( clk : in  STD_LOGIC;
           sclk : out  STD_LOGIC);
end slowClock;

architecture Behavioral of slowClock is


signal slow_clk: STD_LOGIC;
signal counter : STD_LOGIC_VECTOR (31 downto 0);

begin

	process(clk)
	
	begin
		IF (clk'EVENT and clk = '1') THEN  -- On rising edge of clock signal
		
			IF (counter = "00000000000000001000000000000000") THEN
				slow_clk <= not slow_clk; -- toggle the slow clock
				counter <= "00000000000000000000000000000000";
			ELSE
				counter <= counter + 1;
			END IF;
			
			
		END IF;
		
	end process;
	
	sclk <= slow_clk;
	
end Behavioral;

