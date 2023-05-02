import React from 'react';
import WeatherComponent from './WeatherComponent';

export default function WeatherBlock({
  days,
  afternoon,
  evening,
  morning,
  night,
  whole_day,
}) {
  function getMonthName(monthNumber) {
    const date = new Date();
    date.setMonth(monthNumber);
    return date.toLocaleString('en-US', { month: 'long' });
  }
  const fullDate = new Date(days);
  const formatedDate =
    fullDate.getDate() + ' ' + getMonthName(fullDate.getMonth());

  return (
    <div className='p-3 rounded-xl m-4 bg-green-500 flex flex-col'>
      <h2 className='text-lg p-3'>{formatedDate}</h2>
      <div className='weather-blocks flex gap-2'>
        <WeatherComponent dateTime={'Morning'} data={morning} />
        <WeatherComponent dateTime={'Afternoon'} data={afternoon} />
        <WeatherComponent dateTime={'Evening'} data={evening} />
        <WeatherComponent dateTime={'Night'} data={night} />
      </div>
    </div>
  );
}
