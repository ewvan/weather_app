import React, { useEffect, useState } from 'react';
import './App.css';
import config from '/src/config.json';
import fetchData from './utilities/fetch.js';
import Header from './components/Header';
import Main from './components/Main';
import { ColorRing } from 'react-loader-spinner';

const App = () => {
  async function fetchWeather() {
    const response = await fetchData();
    setWeather(response);
    setIsLoaded(true);
  }
  function eventHandler(e) {
    if (e.code == 'Equal') {
      setDays(days++ % 16);
    }
    if (e.code == 'Minus') {
      setDays(days > 0 ? days-- : 0);
    }
    if (e.code == 'KeyN') {
      // setIsLoaded(false);
      setNumberWeather(numberWeather++ % weatherLength);
      console.log(numberWeather);
    }
    if (e.code == 'KeyP') {
      // setIsLoaded(false);
      setNumberWeather(Math.abs(numberWeather--) % weatherLength);
      console.log(numberWeather);
    }
  }
  const weatherLength = config.cities.length;

  let [weather, setWeather] = useState([]);
  let [isLoaded, setIsLoaded] = useState(false);

  let [days, setDays] = useState(config.days);
  let [numberWeather, setNumberWeather] = useState(0);
  useEffect(() => {
    document.addEventListener('keydown', eventHandler);
    fetchWeather();
    return () => {
      document.removeEventListener('keydown', eventHandler);
    };
  }, []);

  let renderedData = weather[numberWeather];
  return (
    <div>
      {isLoaded ? (
        <>
          <Header city={renderedData[0]} />
          <Main data={renderedData[1]} days={days} />
        </>
      ) : (
        <div className='grid h-screen place-items-center'>
          <ColorRing
            visible={true}
            height='80'
            width='80'
            ariaLabel='blocks-loading'
            wrapperStyle={{}}
            wrapperClass='blocks-wrapper'
            colors={['#849b87']}
          />
        </div>
      )}
    </div>
  );
};

export default App;
